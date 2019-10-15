#include "meta_section_parser.h"
#include <algorithm>
#include "Node.h"

namespace hoops {
MetaSectionParser::~MetaSectionParser() {}

MetaSectionParser::MetaSectionParser() {
  parse_map = {{kPronunciationTag, [&](const std::string) { return ""; }}};
}
bool MetaSectionParser::Parse(CNode* node) { return true; }

std::string MetaSectionParser::ParsePronunciation(std::string text) {
  return "";
}

std::string MetaSectionParser::ParsePosition(std::string text) { return ""; }

std::string MetaSectionParser::ParseShoots(std::string text) {
  text.erase(std::remove_if(text.begin(), text.end(), std::isspace),
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