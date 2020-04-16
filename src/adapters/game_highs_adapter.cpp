#include "game_highs_adapter.h"

#include <iostream>
#include "util.h"

namespace hoops {

void GameHighsAdapter::AddAttribute(const std::string& attribute,
                                    std::string value) {
  if (season()->empty()) return;
  if (attribute == "Season") {
    season()->back().season_info.season = value;
  } else if (attribute == "age") {
    season()->back().season_info.age = int_or_negative(value);
  } else if (attribute == "team_id") {
    season()->back().season_info.team = value;
  } else if (attribute == "lg_id") {
    season()->back().season_info.league = value;
  } else if (attribute == "mp") {
    season()->back().minutes_played = value;
  } else if (attribute == "fg") {
    season()->back().field_goals_made = int_or_negative(value);
  } else if (attribute == "fga") {
    season()->back().field_goals_attempt = int_or_negative(value);
  } else if (attribute == "fg3") {
    season()->back().three_points_made = int_or_negative(value);
  } else if (attribute == "fg3a") {
    season()->back().three_points_attempt = int_or_negative(value);
  } else if (attribute == "fg2") {
    season()->back().two_points_made = int_or_negative(value);
  } else if (attribute == "fg2a") {
    season()->back().two_points_attempt = int_or_negative(value);
  } else if (attribute == "ft") {
    season()->back().free_throws_made = int_or_negative(value);
  } else if (attribute == "fta") {
    season()->back().free_throws_attempt = int_or_negative(value);
  } else if (attribute == "orb") {
    season()->back().offensive_rebounds = int_or_negative(value);
  } else if (attribute == "drb") {
    season()->back().defensive_rebounds = int_or_negative(value);
  } else if (attribute == "trb") {
    season()->back().total_rebounds = int_or_negative(value);
  } else if (attribute == "ast") {
    season()->back().assists = int_or_negative(value);
  } else if (attribute == "stl") {
    season()->back().steals = int_or_negative(value);
  } else if (attribute == "blk") {
    season()->back().blocks = int_or_negative(value);
  } else if (attribute == "tov") {
    season()->back().turnovers = int_or_negative(value);
  } else if (attribute == "pf") {
    season()->back().personal_fouls = int_or_negative(value);
  } else if (attribute == "pts") {
    season()->back().points = int_or_negative(value);
  } else if (attribute == "game_score") {
    season()->back().game_score = float_or_negative(value);
  }
}

void GameHighsAdapter::SetSeason() {
  season_ = &player()->career_info.game_highs_seasons;
}

}  // namespace hoops