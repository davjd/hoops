#include "gumbo_scraper.h"

#include "adapters/attribute_adapter.h"
#include "util.h"

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <iostream>
#include <list>
#include <string>
#include <utility>

namespace hoops {

GumboScraper::GumboScraper(CDocument* scraper)
    : meta_parser_(std::make_unique<MetaSectionParser>()),
      adapters_(std::make_unique<StatsAdapters>()) {
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
    FillBadgeData(mutable_player, badge_section.nodeAt(0));
  } else {
    std::cout << "ul #bling was not found.\n";
  }

  auto uniform_section = table.find("div .uni_holder");
  if (uniform_section.nodeNum() != 0) {
    std::cout << "uniform_section: "
              << uniform_section.nodeAt(0).text().substr(0, 100) << "\n";
    FillUniformData(mutable_player, uniform_section.nodeAt(0));
  } else {
    std::cout << "div .uni_holder was not found.\n";
  }

  auto stats_section = table.find("div .stats_pullout");
  if (stats_section.nodeNum() != 0) {
    std::cout << "stats_section: "
              << stats_section.nodeAt(0).text().substr(0, 100) << "\n";
    FillStatsData(mutable_player, stats_section.nodeAt(0));
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

void GumboScraper::FillMetaSection(PlayerMetadata* player, CNode meta_section) {
  // Get media and person sections.
  CSelection media_sel = meta_section.find("div .media-item > img");

  // Extract the image source.
  if (media_sel.nodeNum() != 0 &&
      !media_sel.nodeAt(0).attribute("src").empty()) {
    std::cout << "src: " << media_sel.nodeAt(0).attribute("src") << "\n";
  }

  // Get the info section containing the metadata.
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
  bool pronunciation_found = false;
  CNode pron_node =
      GetNodeThatContains(strong_sel, "p > strong", "Pronunciation");
  if (pron_node.valid()) {
    // Whether the pronunciation label is found determines where the full name
    // and twitter section are, so we'll store this information for later.
    pronunciation_found = true;
    meta_parser_->GetParseFunction("Pronunciation")(&pron_node, player);
  } else {
    std::cout << "No pronunciation data.\n";
  }

  CNode full_name_node = strong_sel.nodeAt(pronunciation_found ? 1 : 0);
  std::cout << "full_name: " << full_name_node.text() << "\n";
  CSelection twitter_sel = full_name_node.parent().find("a[href*='twitter']");
  if (twitter_sel.nodeNum() > 1) {
    std::cout << "twitter: " << twitter_sel.nodeAt(1).text() << "\n";
  } else {
    std::cout << "No twitter: " << twitter_sel.nodeNum() << "\n";
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

void GumboScraper::FillBadgeData(PlayerMetadata* player, CNode badge_section) {
  CSelection lis = badge_section.find("ul > li");
  if (lis.nodeNum() == 0) return;
  for (int i = 0; i < lis.nodeNum(); ++i) {
    const std::string achievement = lis.nodeAt(i).text();
    if (achievement.empty()) continue;
    std::cout << "li: " << achievement << "\n";
    player->AddAchievement(achievement);
  }
}

void GumboScraper::FillUniformData(PlayerMetadata* mutable_player,
                                   CNode badge_section) {
  CSelection links = badge_section.find("div > a");
  if (links.nodeNum() == 0) return;
  for (int i = 0; i < links.nodeNum(); ++i) {
    const std::string team = links.nodeAt(i).attribute("data-tip");
    const std::string link = links.nodeAt(i).attribute("href");
    std::string number = links.nodeAt(i).text();
    if (team.empty() || link.empty() || number.empty()) continue;
    std::cout << link << " : " << team << " : " << std::stoi(number) << "\n";
    PlayerMetadata::CareerInformation::TeamInfo team_info = {team, link,
                                                             std::stoi(number)};
    mutable_player->AddTeamInfo(team_info);
  }
}

void GumboScraper::FillStatsData(PlayerMetadata* mutable_player,
                                 CNode badge_section) {
  CSelection divs = badge_section.find("div > div[class^=p]");
  for (int i = 0; i < divs.nodeNum(); ++i) {
    CNode div_node = divs.nodeAt(i);
    CSelection h4_sel = div_node.find("h4.poptip");
    std::cout << divs.nodeAt(i).attribute("class") << ":\n";
    for (int i = 0; i < h4_sel.nodeNum(); ++i) {
      const std::string attribute = h4_sel.nodeAt(i).text();
      if (attribute.empty() && !h4_sel.nodeAt(i).nextSibling().valid() &&
          !h4_sel.nodeAt(i).nextSibling().nextSibling().valid() &&
          !h4_sel.nodeAt(i).nextSibling().nextSibling().nextSibling().valid())
        continue;
      float value = std::stof(
          h4_sel.nodeAt(i).nextSibling().nextSibling().nextSibling().text());
      std::cout << attribute << ": " << value << "\n";
      mutable_player->AddCareerStat(attribute, value);
    }
  }
}

bool GumboScraper::FillNumbers(PlayerMetadata* mutable_player) {
  if (page_type() != BBallReferencePage::PageType::kProfilePage) {
    std::cout << "incorrect page type.\n";
    return false;
  }

  // Get all the nodes that are table wrappers.
  CSelection wrapper_sel = scraper_->find("div.table_wrapper");
  if (wrapper_sel.nodeNum() == 0) {
    std::cout << "Couldn't find table wrappers.\n";
    return false;
  }
  std::cout << "there exists " << wrapper_sel.nodeNum() << " table wrappers.\n";

  // Before we use the adapters, we must give it a player that we're modifying.
  adapters_->SetPlayer(mutable_player);

  // Go through every table wrapper and get the different kinds of stats.
  for (int i = 0; i < wrapper_sel.nodeNum(); ++i) {
    // Get the kind of stat line this is (what section we're looking at).
    CSelection section_sel =
        wrapper_sel.nodeAt(i).find("div.section_heading > h2");
    if (section_sel.nodeNum() == 0) continue;
    CNode section_node = section_sel.nodeAt(0);

    // Clean the section header text if needed.
    std::string section_header = section_node.text();
    if (section_header.empty()) continue;
    if (section_header[0] == ' ') {
      section_header = section_header.substr(1);
    }

    // We can use this text to get the adapter. e.g:
    auto adapter = adapters_->GetAdapter(section_header);
    if (adapter == nullptr) {
      std::cout << section_header << " has no adapter.\n";
      continue;
    }
    std::cout << section_header << "\n";

    // We got the header, now use the table to find the table rows with each
    // season stat line.
    CNode table_node = wrapper_sel.nodeAt(i);
    std::cout << "table-stat: " << table_node.attribute("id") << "\n";

    // TODO: There are sections that don't follow this format, so we'll need to
    // take care of those instances too.
    CSelection table_row_sel = table_node.find(
        "div.table_outer_container > div.overthrow > table.row_summable > "
        "tbody > tr");
    if (table_row_sel.nodeNum() == 0) {
      std::cout << "Couldn't find table rows with season stats.\n";
      continue;
    } else {
      std::cout << "found multiple table rows.\n";
    }

    // Go through each row, as it will have the statline for a season.
    // For testing purposes, we'll only add the first season.
    for (int i = 0; i < 1 && i < table_row_sel.nodeNum(); ++i) {
      auto row_node = table_row_sel.nodeAt(i);
      // Table header will have the season for this stat line.
      CSelection header_sel = row_node.find("th > a");
      if (header_sel.nodeNum() == 0) continue;

      // We have the season here, so add new one then fill it.
      std::cout << "Adding season " << header_sel.nodeAt(0).text() << ".\n";
      adapter->AddSeason();

      // Get all the different stats for this season.
      CSelection stat_sel = row_node.find("td");
      for (int j = 0; j < stat_sel.nodeNum(); ++j) {
        const std::string stat = stat_sel.nodeAt(j).attribute("data-stat");
        if (stat.empty()) {
          std::cout << "Empty stat.\n";
          continue;
        }
        std::cout << "Filling " << stat << "\n";
        adapter->AddAttribute(stat, stat_sel.nodeAt(j).text());
      }
    }
  }
  return true;
}

}  // namespace hoops