#include "meta_section_parser.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include "Document.h"
#include "Node.h"
#include "player_metadata.h"
#include "util.h"

namespace hoops {
const std::array<std::pair<std::string, MetaSectionParser::ParseFunctor>, 12>
    MetaSectionParser::kParseFunctions = {
        {{"Pronunciation",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid() || sib.text().empty()) return;
            mutable_player->AddAttribute("pronunciation", sib.text());
            mutable_player->AddAttribute("pronunciation", sib.text());
          }},
         {"Position",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) return;
            std::string text = sib.text();
            auto sep = text.find_first_of('\n', 1);
            if (sep == std::string::npos) return;
            text = text.substr(0, sep);
            trim_new_line(&text);
            text = text.substr(2);
            mutable_player->AddAttribute("position", text);
          }},
         {"Shoots",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "SHOOTS No sibilings...\n";
              return;
            }
            // Now get text if it contains it.
            if (sib.tag().empty()) {
              std::string text = sib.text();
              if (text.empty()) return;
              trim_new_line(&text);
              text = text.substr(2);
              mutable_player->AddAttribute("shoots", text);
            }
          }},
         {"Born",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CSelection span_sel = node->parent().find("p > span");
            CSelection age_span_sel = span_sel.find("span:contains('Age')");
            if (age_span_sel.nodeNum() == 1) {
              mutable_player->AddAttribute("age",
                                           age_span_sel.nodeAt(0).text());
            }

            CSelection date_span_sel =
                span_sel.find("p > span[itemprop~='birthDate']");
            if (date_span_sel.nodeNum() == 1) {
              std::string text = date_span_sel.nodeAt(0).text();
              trim_new_line(&text);
              int comma = text.find(",");
              if (comma != std::string::npos) {
                text = text.substr(0, comma + 1) + text.substr(comma + 12);
              }
              mutable_player->AddAttribute("birth_date", text);
            }

            CSelection place_span_sel =
                span_sel.find("p > span[itemprop~='birthPlace']");
            if (place_span_sel.nodeNum() == 1) {
              std::string text = place_span_sel.nodeAt(0).text();
              trim_new_line(&text);
              text = text.substr(4);
              mutable_player->AddAttribute("birth_location", text);
            }
          }},
         {"College",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CSelection span_sel = node->parent().find("p > a");
            if (span_sel.nodeNum() < 1) return;
            auto college_node = span_sel.nodeAt(0);
            mutable_player->AddAttribute("college", college_node.text());
            mutable_player->AddAttribute("college_url",
                                         college_node.attribute("href"));
          }},
         {"High School",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "No sibilings...\n";
              return;
            }
            if (sib.tag().empty()) {
              std::string text = sib.text();
              if (text.empty()) return;
              trim_new_line(&text);
              text = text.substr(2);
              int comma_pos = text.find(",");
              if (comma_pos != std::string::npos) {
                text = text.substr(0, ++comma_pos);
              }
              sib = sib.nextSibling();
              if (sib.valid()) {
                text += " " + sib.text();
              }
              // TODO: Maybe remove the "in" part of the text?
              mutable_player->AddAttribute("high_school", text);
            }
          }},
         {"Draft",
          [](CNode* node, PlayerMetadata* mutable_player) {
            for (CNode sib = node->nextSibling(); sib.valid();
                 sib = sib.nextSibling()) {
              if (sib.tag().empty()) {
                std::string text = sib.text();
                if (!text.empty()) {
                  trim_new_line(&text);
                  mutable_player->AddAttribute("draft", text.substr(1));
                }
              } else if (sib.tag() == "a") {
                std::string link = sib.attribute("href");
                if (link.find("/teams/") != std::string::npos) {
                  mutable_player->AddAttribute("draft_team_url", link);
                  mutable_player->AddAttribute("draft_team", sib.text());
                } else if (link.find("draft/NBA") != std::string::npos) {
                  mutable_player->AddAttribute("draft_year_url", link);
                  mutable_player->AddAttribute("draft_year", sib.text());
                }
              }
            }
          }},
         {"Experience",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "No sibilings...\n";
              return;
            }
            std::string text = sib.text();
            trim_new_line(&text);
            mutable_player->AddAttribute("experience", text.substr(2));
          }},
         {"Physical",
          [](CNode* node, PlayerMetadata* mutable_player) {
            // Note: parent node is passed (since this metadata doesn't actually
            // have label).
            if (!node->valid() || node->childNum() == 0) return;
            // node->text() has integer metrics, might want to use them.
            for (int i = 0; i < node->childNum(); ++i) {
              if (node->childAt(i).tag() == "span") {
                if (node->childAt(i).attribute("itemprop") == "height") {
                  mutable_player->AddAttribute("height",
                                               node->childAt(i).text());
                } else if (node->childAt(i).attribute("itemprop") == "weight") {
                  mutable_player->AddAttribute("weight",
                                               node->childAt(i).text());
                }
              }
            }
          }},
         {"Recruiting Rank",
          [](CNode* node, PlayerMetadata* mutable_player) {
            for (CNode sib = node->nextSibling(); sib.valid();
                 sib = sib.nextSibling()) {
              if (sib.tag().empty()) {
                std::string text = sib.text();
                if (!text.empty()) {
                  trim_new_line(&text);
                  mutable_player->AddAttribute("recruiting_rank",
                                               text.substr(1));
                }
              } else if (sib.tag() == "a") {
                mutable_player->AddAttribute("recruiting_rank_year",
                                             sib.text());
                mutable_player->AddAttribute("recruiting_rank_year_url",
                                             sib.attribute("href"));
              }
            }
          }},
         {"Hall of Fame",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "HALL OF FAME No sibilings...\n";
              return;
            }
            std::string text = sib.text();
            trim_new_line(&text);
            mutable_player->AddAttribute("hall_of_fame", text);
            mutable_player->AddAttribute(
                "hall_of_fame_url",
                node->parent().find("p > a").nodeAt(0).attribute("href"));
          }},
         {"NBA Debut", [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "NBA DEBUT: No sibilings...\n";
              return;
            }
            mutable_player->AddAttribute("nba_debut", sib.text());
            mutable_player->AddAttribute("nba_debut_url",
                                         sib.attribute("href"));
          }}}};

MetaSectionParser::~MetaSectionParser() {}

MetaSectionParser::MetaSectionParser() {}

MetaSectionParser::ParseFunctor MetaSectionParser::GetParseFunction(
    const std::string& tag) {
  auto tag_parser = std::find_if(kParseFunctions.begin(), kParseFunctions.end(),
                                 [&](auto pair) { return pair.first == tag; });
  if (tag_parser != std::end(kParseFunctions)) {
    return tag_parser->second;
  }
  return {};
}

const std::string MetaSectionParser::kPronunciationTag = "Pronunciation";
const std::string MetaSectionParser::kPositionTag = "Position";
const std::string MetaSectionParser::kShootsTag = "Shoots";
const std::string MetaSectionParser::kBornTag = "Born";
const std::string MetaSectionParser::kCollegeTag = "College";
const std::string MetaSectionParser::kHighSchoolTag = "High School";
const std::string MetaSectionParser::kDraftTag = "Draft";
const std::string MetaSectionParser::kNBADebutTag = "NBA Debut";
const std::string MetaSectionParser::kHallofFameTag = "Hall of Fame";
const std::string MetaSectionParser::kExperienceTag = "Experience";
const std::string MetaSectionParser::kRecruitingRankTag = "Recruiting Rank";
}  // namespace hoops