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
            std::cout << "pronunciation: " << sib.text() << "\n";
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
            std::cout << "Position: " << text << "\n";
          }},
         {"Shoots",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "No sibilings...\n";
              return;
            }
            // Now get text if it contains it.
            if (sib.tag().empty()) {
              std::string text = sib.text();
              if (text.empty()) return;
              trim_new_line(&text);
              text = text.substr(2);
              std::cout << "Shoots: " << text << "\n";
              mutable_player->AddAttribute("shoots", text);
            }
          }},
         {"Born",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CSelection span_sel = node->parent().find("p > span");

            // nobr tag isn't fetched by CURL for some reason, so we'll manually
            // calculate days age.

            CSelection age_span_sel = span_sel.find("span:contains('Age')");
            if (age_span_sel.nodeNum() == 1) {
              std::cout << "age: " << age_span_sel.nodeAt(0).text() << "\n";
            } else {
              std::cout << "couldn't find age..\n";
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
              std::cout << "date: " << text << "\n";
            }

            CSelection place_span_sel =
                span_sel.find("p > span[itemprop~='birthPlace']");
            if (place_span_sel.nodeNum() == 1) {
              std::string text = place_span_sel.nodeAt(0).text();
              trim_new_line(&text);
              text = text.substr(4);
              std::cout << "location: " << text << "\n";
            }
          }},
         {"College",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CSelection span_sel = node->parent().find("p > a");
            if (span_sel.nodeNum() < 1) return;
            std::cout << span_sel.nodeAt(0).text() << "\n";
            auto college_node = span_sel.nodeAt(0);
            std::cout << "college: " << college_node.text() << ": "
                      << college_node.attribute("href") << "\n";
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
              std::cout << "High school: " << text << "\n";
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
                  std::cout << "draft: " << text.substr(1) << "\n";
                }
              } else if (sib.tag() == "a") {
                std::string link = sib.attribute("href");
                if (link.find("/teams/") != std::string::npos) {
                  std::cout << "team: " << sib.text() << ": " << link << "\n";
                } else if (link.find("draft/NBA") != std::string::npos) {
                  std::cout << "year: " << sib.text() << ": " << link << "\n";
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
            std::cout << "experience: " << text.substr(2) << "\n";
          }},
         {"Physical",
          [](CNode* node, PlayerMetadata* mutable_player) {
            // Note: parent node is passed (since this metadata doesn't actually
            // have label).
            if (!node->valid() || node->childNum() == 0) return;
            std::cout << node->text() << "\n";
            for (int i = 0; i < node->childNum(); ++i) {
              if (node->childAt(i).tag() == "span") {
                if (node->childAt(i).attribute("itemprop") == "height") {
                  std::cout << "height: " << node->childAt(i).text() << "\n";
                } else if (node->childAt(i).attribute("itemprop") == "weight") {
                  std::cout << "weight: " << node->childAt(i).text() << "\n";
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
                  std::cout << "rank: " << text.substr(1) << "\n";
                }
              } else if (sib.tag() == "a") {
                std::cout << "link: " << sib.text() << ": "
                          << sib.attribute("href") << "\n";
              }
            }
          }},
         {"Hall of Fame",
          [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "No sibilings...\n";
              return;
            }
            std::string text = sib.text();
            trim_new_line(&text);
            std::cout << "hof: " << text << "\n";
            std::cout << "year: "
                      << node->parent().find("p > a").nodeAt(0).attribute(
                             "href");
          }},
         {"NBA Debut", [](CNode* node, PlayerMetadata* mutable_player) {
            if (!node->valid()) return;
            CNode sib = node->nextSibling();
            if (!sib.valid()) {
              std::cout << "No sibilings...\n";
              return;
            }
            std::cout << "debut: " << sib.text() << ": "
                      << sib.attribute("href") << "\n";
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

bool MetaSectionParser::Parse(CNode* node, const std::string& tag) {
  return true;
}
void MetaSectionParser::ParseTag(const std::string& tag) {
  // auto tag_parser =
  //     std::find(kParseFunctions.begin(), kParseFunctions.end(), tag);
  // if (tag_parser != kParseFunctions.end()) {
  //   // tag_parser.second();
  // }
}

std::string MetaSectionParser::ParsePronunciation(std::string text) {
  return "";
}

std::string MetaSectionParser::ParsePosition(std::string text) { return ""; }

std::string MetaSectionParser::ParseShoots(std::string text) {
  text.erase(std::remove_if(text.begin(), text.end(),
                            [](unsigned char c) { return std::isspace(c); }),
             text.end());
  return text;
}
std::string MetaSectionParser::ParseBorn(std::string text) { return ""; }
std::string MetaSectionParser::ParseCollege(std::string text) { return ""; }
std::string MetaSectionParser::ParseHighSchool(std::string text) { return ""; }
std::string MetaSectionParser::ParseDraft(std::string text) { return ""; }

std::string MetaSectionParser::ParseNBADebut(std::string text) { return ""; }

std::string MetaSectionParser::ParseHallofFame(std::string text) { return ""; }

std::string MetaSectionParser::ParseExperience(std::string text) { return ""; }

std::string MetaSectionParser::ParseRecruitingRank(std::string text) {
  return "";
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