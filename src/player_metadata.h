#ifndef PLAYER_METADATA_H_
#define PLAYER_METADATA_H_

#include <array>
#include <string>
#include <utility>

namespace hoops {

class PlayerMetadata {
 public:
  void AddAttribute(const std::string& attribute, const std::string& value);
  std::string GetFullUrl();
  std::string GetFullName();
  static std::string GetFirstName(const std::string& full_name);
  static std::string GetLastName(const std::string& full_name);
  void AddSchoolInformation(const std::string& attribute,
                            const std::string& value);
  void AddIDInformation(const std::string& attribute, const std::string& value);
  void AddPhysicalInformation(const std::string& attribute,
                              const std::string& value);
  void AddCareerInformation(const std::string& attribute,
                            const std::string& value);

  struct SchoolInformation {
    std::string college;
    std::string college_url;
    std::string high_school;
    std::string high_school_url;
  } school_info;

  static const std::array<std::string, 4> school_tags;

  struct IDInformation {
    std::string first_name;
    std::string last_name;
    std::string url;
    std::string birth_date;
    std::string born;
    std::string born_date_url;
    std::string born_home_url;
    std::string born_year_url;
    std::string legal_name;
    std::string twitter;
  } id_info;

  static const std::array<std::string, 10> id_tags;

  struct PhysicalInformation {
    std::string position;
    std::string height;
    int weight;
    std::string shoots;
  } physical_info;

  static const std::array<std::string, 4> physical_tags;

  struct CareerInformation {
    int start_year;
    int end_year;
    std::string draft;
    std::string draft_team_url;
    std::string draft_year_url;
    std::string nba_debut;
    std::string nba_debut_url;
    int recruiting_rank;
    int recruiting_rank_year;
    std::string recruiting_rank_year_url;
    bool in_hall_of_fame;
  } career_info;

  static const std::array<std::string, 11> career_tags;
};

}  // namespace hoops

#endif  // PLAYER_METADATA_H_