#include "player_metadata.h"
#include "env_namespace.h"

#include <algorithm>
#include <iostream>

namespace hoops {

const std::array<std::string, 10> PlayerMetadata::id_tags = {
    "first_name",    "last_name",     "url",           "birth_date", "born",
    "born_date_url", "born_home_url", "born_year_url", "legal_name", "twitter"};
const std::array<std::string, 4> PlayerMetadata::school_tags = {
    "college", "college_url", "high_school", "high_school_url"};
const std::array<std::string, 4> PlayerMetadata::physical_tags = {
    "position", "height", "weight", "shoots"};
const std::array<std::string, 11> PlayerMetadata::career_tags = {
    "start_year",
    "end_year",
    "draft",
    "draft_team_url",
    "draft_year_url",
    "nba_debut",
    "nba_debut_url",
    "recruiting_rank",
    "recruiting_rank_year",
    "recruiting_rank_year_url",
    "in_hall_of_fame"};

void PlayerMetadata::AddAttribute(const std::string& attribute,
                                  const std::string& value) {
  if (std::find(school_tags.begin(), school_tags.end(), attribute) !=
      school_tags.end()) {
    AddSchoolInformation(attribute, value);
  }
  if (std::find(id_tags.begin(), id_tags.end(), attribute) != id_tags.end()) {
    AddIDInformation(attribute, value);
  }
  if (std::find(id_tags.begin(), id_tags.end(), attribute) != id_tags.end()) {
    AddIDInformation(attribute, value);
  }
  if (std::find(physical_tags.begin(), physical_tags.end(), attribute) !=
      physical_tags.end()) {
    AddPhysicalInformation(attribute, value);
  }
  if (std::find(career_tags.begin(), career_tags.end(), attribute) !=
      career_tags.end()) {
    AddCareerInformation(attribute, value);
  }
}

void PlayerMetadata::AddSchoolInformation(const std::string& attribute,
                                          const std::string& value) {
  std::cout << "Adding " << attribute << "with " << value << "\n";
  if (attribute == "college") {
    school_info.college = value;
  } else if (attribute == "college_url") {
    school_info.college_url = value;
  } else if (attribute == "high_school") {
    school_info.high_school = value;
  } else if (attribute == "high_school_url") {
    school_info.high_school_url = value;
  } else {
    std::cout << "Couldn't add attribute: " << attribute << "\n";
  }
}

void PlayerMetadata::AddIDInformation(const std::string& attribute,
                                      const std::string& value) {
  if (attribute == "first_name") {
    id_info.first_name = value;
  } else if (attribute == "last_name") {
    id_info.last_name = value;
  } else if (attribute == "url") {
    id_info.url = value;
  } else if (attribute == "birth_date") {
    id_info.birth_date = value;
  } else if (attribute == "born") {
    id_info.born = value;
  } else if (attribute == "born_date_url") {
    id_info.born_date_url = value;
  } else if (attribute == "born_home_url") {
    id_info.born_home_url = value;
  } else if (attribute == "born_year_url") {
    id_info.born_year_url = value;
  } else if (attribute == "legal_name") {
    id_info.legal_name = value;
  } else if (attribute == "twitter") {
    id_info.twitter = value;
  } else {
    std::cout << "Couldn't add attribute: " << attribute << "\n";
  }
}

void PlayerMetadata::AddPhysicalInformation(const std::string& attribute,
                                            const std::string& value) {
  if (attribute == "height") {
    physical_info.height = value;
  } else if (attribute == "weight") {
    if (attribute.empty()) return;
    physical_info.weight = std::stoi(value);
  } else if (attribute == "shoots") {
    physical_info.shoots = value;
  } else {
    std::cout << "Couldn't add attribute: " << attribute << "\n";
  }
}

void PlayerMetadata::AddCareerInformation(const std::string& attribute,
                                          const std::string& value) {
  if (attribute == "start_year") {
    if (attribute.empty()) return;
    career_info.start_year = std::stoi(value);
  } else if (attribute == "end_year") {
    if (attribute.empty()) return;
    career_info.end_year = std::stoi(value);
  } else if (attribute == "draft") {
    career_info.draft = value;
  } else if (attribute == "draft_team_url") {
    career_info.draft_team_url = value;
  } else if (attribute == "draft_year_url") {
    career_info.draft_year_url = value;
  } else if (attribute == "nba_debut") {
    career_info.nba_debut = value;
  } else if (attribute == "nba_debut_url") {
    career_info.nba_debut_url = value;
  } else if (attribute == "recruiting_rank") {
    if (attribute.empty()) return;
    career_info.recruiting_rank = std::stoi(value);
  } else if (attribute == "recruiting_rank_year") {
    if (attribute.empty()) return;
    career_info.recruiting_rank_year = std::stoi(value);
  } else if (attribute == "recruiting_rank_year_url") {
    career_info.recruiting_rank_year_url = value;
  } else if (attribute == "in_hall_of_fame") {
    // TODO : this attribute might not be needed.
    career_info.in_hall_of_fame = value == "y" ? true : false;
  } else {
    std::cout << "Couldn't add attribute: " << attribute << "\n";
  }
}

void PlayerMetadata::AddAchievement(const std::string& achievement) {
  career_info.achievements.push_back(achievement);
}

PlayerMetadata::CareerInformation::CareerStats
PlayerMetadata::GetCareerStats() {
  return career_info.career_stats;
}

void PlayerMetadata::AddCareerStat(const std::string& stat_type, float value) {
  // TODO: This style of setting values isn't scalable. Maybe instead implement
  // adapters that translate html tags to internal representations of those
  // tags.
  if (stat_type == "G") {
    career_info.career_stats.total_games = value;
  } else if (stat_type == "PTS") {
    career_info.career_stats.pts = value;
  } else if (stat_type == "TRB") {
    career_info.career_stats.trb = value;
  } else if (stat_type == "AST") {
    career_info.career_stats.ast = value;
  } else if (stat_type == "FG%") {
    career_info.career_stats.fgp = value;
  } else if (stat_type == "FG3%") {
    career_info.career_stats.fg3p = value;
  } else if (stat_type == "FT%") {
    career_info.career_stats.ftp = value;
  } else if (stat_type == "eFG%") {
    career_info.career_stats.efgp = value;
  } else if (stat_type == "PER") {
    career_info.career_stats.per = value;
  } else if (stat_type == "WS") {
    career_info.career_stats.ws = value;
  }
}

void PlayerMetadata::AddTeamInfo(
    PlayerMetadata::CareerInformation::TeamInfo team_info) {
  career_info.team_info.push_back(team_info);
}

std::string PlayerMetadata::GetFullName() {
  return id_info.first_name + " " + id_info.last_name;
}

std::string PlayerMetadata::GetFirstName(const std::string& full_name) {
  auto space_pos = full_name.find(' ');
  if (space_pos == std::string::npos) return "";
  return full_name.substr(0, space_pos);
}

std::string PlayerMetadata::GetLastName(const std::string& full_name) {
  auto space_pos = full_name.find(' ');
  if (space_pos == std::string::npos) return "";
  if (++space_pos >= full_name.size() - 1) return "";
  return full_name.substr(space_pos);
}

std::string PlayerMetadata::GetFullUrl() {
  return env::url::kBaseUrl + id_info.url;
}

}  // namespace hoops