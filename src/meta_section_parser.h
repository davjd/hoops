#ifndef META_SECTION_PARSER_H_
#define META_SECTION_PARSER_H_

#include <array>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class CNode;

namespace hoops {
class PlayerMetadata;

class MetaSectionParser {
 public:
  using ParseFunctor = std::function<void(CNode*, PlayerMetadata*)>;
  ~MetaSectionParser();
  MetaSectionParser();
  ParseFunctor GetParseFunction(const std::string& tag);

 private:
  std::vector<std::string> meta_labels;
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

  static const std::array<std::pair<std::string, ParseFunctor>, 12>
      kParseFunctions;
};
}  // namespace hoops
#endif  // META_SECTION_PARSER_H_