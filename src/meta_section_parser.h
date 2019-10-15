#ifndef META_SECTION_PARSER_H_
#define META_SECTION_PARSER_H_

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class CNode;

namespace hoops {

class MetaSectionParser {
 public:
  ~MetaSectionParser();
  MetaSectionParser();
  bool Parse(CNode* node);

  std::string ParsePronunciation(std::string text);
  std::string ParsePosition(std::string text);
  std::string ParseShoots(std::string text);
  std::string ParseBorn(std::string text);
  std::string ParseCollege(std::string text);
  std::string ParseHighSchool(std::string text);
  std::string ParseDraft(std::string text);
  std::string ParseNBADebut(std::string text);
  std::string ParseHallofFame(std::string text);
  std::string ParseExperience(std::string text);
  std::string ParseRecruitingRank(std::string text);

 private:
  std::vector<std::string> meta_labels;
  std::unordered_map<std::string, std::function<std::string(std::string)>>
      parse_map;
  static const std::string kPronunciationTag;
  static const std::string kPositionTag;
  static const std::string kShootsTag;
  static const std::string kBornTag;
  static const std::string kCollegeTag;
  static const std::string kHighSchoolTag;
  static const std::string kDraftTag;
  static const std::string kNBADebutTag;
  static const std::string kHallofFameTag;
  static const std::string kExperienceTag;
  static const std::string kRecruitingRankTag;
};
}  // namespace hoops
#endif  // META_SECTION_PARSER_H_