#include "gumbo_scraper.h"
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <iostream>
#include <list>
#include <utility>
#include "util.h"

namespace hoops {

GumboScraper::GumboScraper(CDocument* scraper)
    : meta_parser_(std::make_unique<MetaSectionParser>()) {
  set_scraper(scraper);
}

GumboScraper::GumboScraper() : GumboScraper(new CDocument()) {}

void GumboScraper::SetPageContent(const std::string& content,
                                  const std::string& url) {
  SetPage(new BBallReferencePage(content, url));
}

void GumboScraper::SetPage(ContentPage* page) {
  ScraperWrapper<CDocument>::SetPage(page);
  auto page_cast = static_cast<BBallReferencePage*>(page);
  page_type_ = page_cast->GetPageType();
  std::cout << "page type internal: " << page_type_ << "\n";
  std::string content_copy = page->content();
  if (content_copy.size() != 0) scraper_->parse(content_copy);
}

// Gets <body> tag of HTML page.
std::string GumboScraper::GetBody() {
  if (IsEmpty()) return "";
  return CurrentPage()->content();
}

// Checks if current page is empty.
bool GumboScraper::IsEmpty() { return !scraper_->isInitialized(); }

std::string GumboScraper::GetPlayerNames() {
  std::string result = "";
  if (IsEmpty() || page_type() != BBallReferencePage::PageType::kIndexPage)
    return result;
  CSelection selection = scraper_->find("table#players tbody");
  if (selection.nodeNum() == 0) return "";

  CNode table = selection.nodeAt(0);
  for (int i = 0; i < table.childNum(); ++i) {
    CNode row = table.childAt(i);
    if (row.attribute("class") == "thead") continue;

    CSelection header_selection = row.find("th");
    if (header_selection.nodeNum() == 0) continue;

    CNode header = header_selection.nodeAt(0);
    CNode child = header.childAt(0);
    result.append(child.text() + ", ");
  }
  return result;
}

std::vector<PlayerMetadata> GumboScraper::GetPlayers() {
  std::vector<PlayerMetadata> players;
  if (IsEmpty() || page_type() != BBallReferencePage::PageType::kIndexPage)
    return players;
  CSelection sel = scraper_->find("table#players tbody");
  if (sel.nodeNum() == 0) {
    return players;
  }

  CNode table = sel.nodeAt(0);
  for (int i = 0; i < table.childNum(); ++i) {
    PlayerMetadata player;
    CNode tr = table.childAt(i);
    if (tr.attribute("class") == "thead") continue;

    CSelection header_selection = tr.find("th");
    if (header_selection.nodeNum() == 0) continue;

    CNode header = header_selection.nodeAt(0);
    CNode header_child = header.childAt(0);
    std::string name = header.text();
    // Find out if the name has an asterik.
    int asterik_pos = name.find("*");
    if (asterik_pos != std::string::npos) {
      name = name.substr(0, asterik_pos);
      player.AddAttribute("in_hall_of_fame", "y");
    }
    player.AddAttribute("first_name", PlayerMetadata::GetFirstName(name));
    player.AddAttribute("last_name", PlayerMetadata::GetLastName(name));
    player.AddAttribute("url", header_child.tag() == "a"
                                   ? header_child.attribute("href")
                                   : header_child.childAt(0).attribute("href"));

    CSelection cells = tr.find("td");
    for (int j = 0; j < cells.nodeNum(); ++j) {
      CNode cell = cells.nodeAt(j);
      player.AddAttribute(cell.attribute("data-stat"), cell.text());
    }
    players.push_back(player);
  }
  return players;
}

PlayerMetadata GumboScraper::GetPlayer(const std::string& player_name) {
  PlayerMetadata player;
  if (IsEmpty() || page_type() != BBallReferencePage::PageType::kProfilePage)
    return player;
  CSelection sel = scraper_->find("table#players tbody");
  if (sel.nodeNum() == 0) {
    return player;
  }

  CNode table = sel.nodeAt(0);
  for (int i = 0; i < table.childNum(); ++i) {
    CNode tr = table.childAt(i);
    if (tr.attribute("class") == "thead") continue;

    CSelection header_selection = tr.find("th");
    if (header_selection.nodeNum() == 0) continue;

    CNode header = header_selection.nodeAt(0);
    CNode header_child = header.childAt(0);
    std::string name = header.text();
    std::string lowercase_player_name;
    std::transform(player_name.begin(), player_name.end(),
                   std::back_inserter(lowercase_player_name), tolower);
    std::transform(name.begin(), name.end(), name.begin(), tolower);
    int asterik_pos = name.find("*");
    if (asterik_pos != std::string::npos) {
      name = name.substr(0, asterik_pos);
      player.AddAttribute("in_hall_of_fame", "y");
    }
    if (lowercase_player_name != name) continue;
    player.AddAttribute("first_name", PlayerMetadata::GetFirstName(name));
    player.AddAttribute("last_name", PlayerMetadata::GetLastName(name));
    player.AddAttribute("url", header_child.tag() == "a"
                                   ? header_child.attribute("href")
                                   : header_child.childAt(0).attribute("href"));

    CSelection cells = tr.find("td");
    for (int j = 0; j < cells.nodeNum(); ++j) {
      CNode cell = cells.nodeAt(j);
      player.AddAttribute(cell.attribute("data-stat"), cell.text());
    }
    return player;
  }
  return player;
}

bool GumboScraper::FillPlayerMetadata(PlayerMetadata* mutable_player) {
  if (page_type() != BBallReferencePage::PageType::kProfilePage) {
    std::cout << "incorrect page type.\n";
    return false;
  }
  CSelection sel = scraper_->find("div.players");
  if (sel.nodeNum() == 0) {
    std::cout << "isempty()\n";
    return false;
  }
  std::cout << "there exists " << sel.nodeNum()
            << " findings with such query..\n";
  CNode table = sel.nodeAt(0);

  // Peek content of each section.
  auto meta_section = table.find("div #meta");
  if (meta_section.nodeNum() != 0) {
    std::cout << "meta_section: "
              << meta_section.nodeAt(0).text().substr(0, 100) << "\n";
    FillMetaSection(mutable_player, meta_section.nodeAt(0));
  } else {
    std::cout << "div #meta was not found.\n";
  }

  auto badge_section = table.find("#bling");
  if (badge_section.nodeNum() != 0) {
    std::cout << "badge_section: "
              << badge_section.nodeAt(0).text().substr(0, 100) << "\n";
  } else {
    std::cout << "ul #bling was not found.\n";
  }

  auto college_section = table.find("div .uni_holder");
  if (college_section.nodeNum() != 0) {
    std::cout << "college_section: "
              << college_section.nodeAt(0).text().substr(0, 100) << "\n";
  } else {
    std::cout << "div .uni_holder was not found.\n";
  }

  auto stats_section = table.find("div .stats_pullout");
  if (stats_section.nodeNum() != 0) {
    std::cout << "stats_section: "
              << stats_section.nodeAt(0).text().substr(0, 100) << "\n";
  } else {
    std::cout << "div .stats_pullout was not found.\n";
  }
  return true;
}

CNode GetNodeThatContains(CSelection selection, const std::string& element,
                          const std::string query) {
  CSelection label_sel = selection.find(element + ":contains('" + query + "')");
  if (label_sel.nodeNum() != 0) {
    return label_sel.nodeAt(0);
  }
  std::cout << query << " not found.\n";
  return CNode();
}

CNode GetNodeThatContains(CNode node, const std::string& element,
                          const std::string query) {
  CSelection label_sel = node.find(element + ":contains('" + query + "')");
  if (label_sel.nodeNum() != 0) {
    return label_sel.nodeAt(0);
  }
  std::cout << query << " not found.\n";
  return CNode();
}

// Ignoring nodes of element tag, get the text of sibilings for a given node
// (including the node's text).
std::string GetSibilingTextIgnoring(CNode node, const std::string& tag) {
  std::string full_text = "";
  if (!node.valid()) return full_text;
  CNode sib = node.nextSibling();
  if (!sib.valid()) {
    std::cout << "No sibilings...\n";
    return "";
  }

  for (; sib.valid() && sib.tag() != tag; sib = sib.nextSibling()) {
    std::string sib_text = sib.text();
    if (sib_text.empty()) continue;
    full_text += "<" + sib.tag() + ">" + sib_text + "\n";
  }
  return full_text;
}

// Separate sibiling text ignoring tags with tag 'tag'.
std::string TokenizeSibilingTextIgnoring(const std::string& tag, CNode node) {
  std::list<std::pair<std::string, std::string>> nodes;
  std::string full_text = "";
  if (!node.valid()) return full_text;
  CNode sib = node.nextSibling();
  if (!sib.valid()) {
    std::cout << "No sibilings...\n";
    return "";
  }

  for (; sib.valid() && sib.tag() != tag; sib = sib.nextSibling()) {
    std::string sib_text = sib.text();
    if (sib_text.empty()) continue;
    full_text += "<" + sib.tag() + ">" + sib_text + "\n";
  }
  return full_text;
}

void Parse(CSelection sel) {
  std::cout << "parsing..\n";
  const std::string label = "Recruiting Rank:";
  CSelection label_sel = sel.find("p > strong:contains('" + label + "')");
  if (label_sel.nodeNum() == 0) {
    std::cout << label << " not found.\n";
    return;
  }
  CNode label_node = label_sel.nodeAt(0);
  std::cout << label << "<" << label_node.tag() << ">"
            << ": ";
  CNode sib = label_node.nextSibling();
  if (sib.valid()) {
    for (; sib.valid() && sib.tag() != "strong"; sib = sib.nextSibling()) {
      std::string sib_text = sib.text();
      if (sib_text.empty()) continue;
      std::cout << "<" << sib.tag() << ">" << sib_text << "\n";
    }
  } else {
    std::cout << "No sibs...\n";
  }
}

void GumboScraper::FillMetaSection(PlayerMetadata* player, CNode meta_section) {
  // Get media and person sections.
  CSelection media_sel = meta_section.find("div .media-item > img");
  if (media_sel.nodeNum() != 0 &&
      !media_sel.nodeAt(0).attribute("src").empty()) {
    // Extract the image source.
    std::cout << "src: " << media_sel.nodeAt(0).attribute("src") << "\n";
  }
  CSelection person_sel = meta_section.find("div[itemtype*='Person']");
  if (person_sel.nodeNum() == 0) return;
  CNode info_item = person_sel.nodeAt(0);

  // Find the name section (which might have a twitter section).
  CSelection name_sel = info_item.find("h1[itemprop~='name']");
  if (name_sel.nodeNum() > 0) {
    std::cout << "name: " << name_sel.nodeAt(0).text() << "\n";
  } else {
    std::cout << "Name attribute wasn't found. :(\n";
  }

  // Get all the strong tags that contain meta labels.
  CSelection strong_sel = info_item.find("p > strong");
  if (strong_sel.nodeNum() == 0) {
    return;
  }
  std::vector<std::string> meta_labels = {
      "Pronunciation", "Position:",    "Shoots:",          "Born:",
      "College:",      "High School:", "Draft:",           "NBA Debut:",
      "Hall of Fame:", "Experience:",  "Recruiting Rank:", "Team:"};
  bool pronounciation_found = false;
  // "Twitter:" is not inside a <strong> tag, found in <a>.
  // "Age:" is not inside a <strong> tag, found in attribute.
  for (const std::string& label : meta_labels) {
    CSelection label_sel =
        strong_sel.find("p > strong:contains('" + label + "')");
    if (label_sel.nodeNum() == 0) {
      std::cout << label << " not found.\n";
      continue;
    }
    CNode label_node = label_sel.nodeAt(0);
    std::cout << label << "<" << label_node.tag() << ">"
              << ": ";
    CNode sib = label_node.nextSibling();
    if (sib.valid()) {
      for (; sib.valid() && sib.tag() != "strong"; sib = sib.nextSibling()) {
        std::string sib_text = sib.text();
        if (sib_text.empty()) continue;
        std::cout << "<" << sib.tag() << ">" << sib_text << "\n";
      }
      if (label == meta_labels[0]) {
        pronounciation_found = true;
      }
    } else {
      std::cout << "No sibs...\n";
    }
  }

  CNode full_name_node = strong_sel.nodeAt(pronounciation_found ? 1 : 0);

  std::cout << "full_name: " << full_name_node.text() << "\n";
  CSelection twitter_sel = full_name_node.parent().find("a[href*='twitter']");
  if (twitter_sel.nodeNum() > 1) {
    std::cout << "twitter: " << twitter_sel.nodeAt(1).text() << "\n";
  } else {
    std::cout << "No twitter: " << twitter_sel.nodeNum() << "\n";
  }

  // Parse shoots:
  CNode shoots_node = GetNodeThatContains(strong_sel, "p > strong", "Shoots:");
  if (shoots_node.valid()) {
    meta_parser_->GetParseFunction("Shoots")(&shoots_node, player);
  }

  // Parse position:
  CNode position_node =
      GetNodeThatContains(strong_sel, "p > strong", "Position:");
  if (position_node.valid()) {
    meta_parser_->GetParseFunction("Position")(&position_node, player);

    // Get nicknames if they exist. They will be placed right before the
    // position label. So use that node to get the previous sibiling.
    if (position_node.parent().prevSibling().valid() &&
        position_node.parent().prevSibling().prevSibling().valid()) {
      std::string text =
          position_node.parent().prevSibling().prevSibling().text();
      trim_new_line(&text);
      std::cout << "nickname: " << text << "\n";
    }
  }

  // Parse born:
  CNode born_node = GetNodeThatContains(strong_sel, "p > strong", "Born:");
  if (born_node.valid()) {
    meta_parser_->GetParseFunction("Born")(&born_node, player);
  }

  // Parse college:
  CNode college_node =
      GetNodeThatContains(strong_sel, "p > strong", "College:");
  if (college_node.valid()) {
    meta_parser_->GetParseFunction("College")(&college_node, player);
  } else {
    std::cout << "No college data.\n";
  }

  // Parse high school:
  CNode high_school_node =
      GetNodeThatContains(strong_sel, "p > strong", "High School:");
  if (high_school_node.valid()) {
    meta_parser_->GetParseFunction("High School")(&high_school_node, player);
  } else {
    std::cout << "No high school data.\n";
  }

  // Parse rank:
  CNode rank_node =
      GetNodeThatContains(strong_sel, "p > strong", "Recruiting Rank:");
  if (rank_node.valid()) {
    meta_parser_->GetParseFunction("Recruiting Rank")(&rank_node, player);
  } else {
    std::cout << "No recruiting rank data.\n";
  }

  // Parse NBA Debut:
  CNode debut_node =
      GetNodeThatContains(strong_sel, "p > strong", "NBA Debut:");
  if (debut_node.valid()) {
    meta_parser_->GetParseFunction("NBA Debut")(&debut_node, player);
  } else {
    std::cout << "No debut data.\n";
  }

  // Parse experience:
  CNode exp_node = GetNodeThatContains(strong_sel, "p > strong", "Experience:");
  if (exp_node.valid()) {
    meta_parser_->GetParseFunction("Experience")(&exp_node, player);
  } else {
    std::cout << "No experience data.\n";
  }

  // Parse draft:
  CNode draft_node = GetNodeThatContains(strong_sel, "p > strong", "Draft:");
  if (draft_node.valid()) {
    meta_parser_->GetParseFunction("Draft")(&draft_node, player);
  } else {
    std::cout << "No draft data.\n";
  }

  // Parse physical attributes.
  CSelection height_sel = info_item.find("div > p > span[itemprop~='height']");
  if (height_sel.nodeNum() > 0) {
    CNode height_parent = height_sel.nodeAt(0).parent();
    if (height_parent.valid()) {
      meta_parser_->GetParseFunction("Physical")(&height_parent, player);
    }
  } else {
    std::cout << "No physical data.\n";
  }

  // Parse pronunciation.
  CNode pron_node =
      GetNodeThatContains(strong_sel, "p > strong", "Pronunciation");
  if (pron_node.valid()) {
    meta_parser_->GetParseFunction("Pronunciation")(&pron_node, player);
  } else {
    std::cout << "No pronunciation data.\n";
  }

  // Parse Hall of Fame.
  CNode hof_node =
      GetNodeThatContains(strong_sel, "p > strong", "Hall of Fame:");
  if (hof_node.valid()) {
    meta_parser_->GetParseFunction("Hall of Fame")(&hof_node, player);
  } else {
    std::cout << "No hall of fame data.\n";
  }
}

}  // namespace hoops