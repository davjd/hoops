#include "gumbo_scraper.h"
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <iostream>

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
  auto meta_section = table.find("div #meta");
  if (meta_section.nodeNum() == 0) {
    std::cout << "div #meta was not found.\n";
    return false;
  }
  auto badge_section = table.find("#bling");
  if (badge_section.nodeNum() == 0) {
    std::cout << "ul #bling was not found.\n";
    return false;
  }
  auto college_section = table.find("div .uni_holder");
  if (college_section.nodeNum() == 0) {
    std::cout << "div .uni_holder was not found.\n";
    return false;
  }
  auto stats_section = table.find("div .stats_pullout");
  if (stats_section.nodeNum() == 0) {
    std::cout << "div .stats_pullout was not found.\n";
    return false;
  }

  std::cout << "meta_section: " << meta_section.nodeAt(0).text().substr(0, 100)
            << "\n";
  std::cout << "badge_section: "
            << badge_section.nodeAt(0).text().substr(0, 100) << "\n";
  std::cout << "college_section: "
            << college_section.nodeAt(0).text().substr(0, 100) << "\n";
  std::cout << "stats_section: "
            << stats_section.nodeAt(0).text().substr(0, 100) << "\n";
  FillMetaSection(mutable_player, meta_section.nodeAt(0));
  // for (int i = 0; i < table.childNum(); ++i) {
  //   CNode table_section = table.childAt(i);
  //   if (table_section.tag().empty()) continue;
  //   std::cout << "-------------- childnum: " << i << " " <<
  //   table_section.tag()
  //             << " class " << table_section.attribute("class") << " # "
  //             << table_section.attribute("id") << "------------\n";
  //   std::string content = table_section.text();
  //   std::remove_if(content.begin(), content.end(), isspace);
  //   std::cout << content << "\n\n";
  // }

  // div #meta
  // ul #bling
  // div .uni_holder
  // div .adblock ad300
  // div .stats_pullout

  // auto stats_section = table.find("div.stats_pullout");
  // if (stats_section.nodeNum() == 0) {
  //   std::cout << "isempty()\n";
  //   return false;
  // }

  // auto part1 = stats_section.nodeAt(0).find("div.p1").nodeAt(0);
  // auto sections = part1.find("div");
  // for (int i = 0; i < sections.nodeNum(); ++i) {
  //   std::cout << sections.nodeAt(i).text() << "\n\n ";
  // }

  return true;
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
      "Pronunciation", "Position:",    "Shoots:",         "Born:",
      "College:",      "High School:", "Draft:",          "NBA Debut:",
      "Hall of Fame:", "Experience:",  "Recruiting Rank:"};
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

  std::cout << "Example shoots parse: " << meta_parser_->ParseShoots("  Right")
            << "\n";

  /*
  Pronunciation: \kuh-REEM ab-dool juh-BAR\

Kareem Abdul-Jabbar ▪ Twitter: kaj33

(born Ferdinand Lewis Alcindor Jr.)

(Lew, Cap, Murdock, Big Fella)

Position: Center ▪ Shoots: Right

7-2, 225lb (218cm, 102kg)

Born: April 16, 1947 (Age: 72-172d) in New York, New York us

College: UCLA

High School: Power Memorial in New York, New York

Draft: Milwaukee Bucks, 1st round (1st pick, 1st overall), 1969 NBA Draft

NBA Debut: October 18, 1969

Hall of Fame: Inducted as Player in 1995 (Full List)


  */
}

}  // namespace hoops