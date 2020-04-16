#include "per_game_adapter.h"

#include <iostream>
#include "util.h"

namespace hoops {

void PerGameAdapter::AddAttribute(const std::string& attribute,
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
  } else if (attribute == "pos") {
    season()->back().season_info.position = value;
  } else if (attribute == "g") {
    season()->back().games = float_or_negative(value);
  } else if (attribute == "gs") {
    season()->back().games_started = int_or_negative(value);
  } else if (attribute == "mp_per_g") {
    season()->back().minutes_played = float_or_negative(value);
  } else if (attribute == "fg_per_g") {
    season()->back().field_goals_made = float_or_negative(value);
  } else if (attribute == "fga_per_g") {
    season()->back().field_goals_attempt = float_or_negative(value);
  } else if (attribute == "fg_pct") {
    season()->back().field_goal_percentage = float_or_negative(value);
  } else if (attribute == "fg3_per_g") {
    season()->back().three_points_made = float_or_negative(value);
  } else if (attribute == "fg3a_per_g") {
    season()->back().three_points_attempt = float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    season()->back().three_points_percentage = float_or_negative(value);
  } else if (attribute == "fg2_per_g") {
    season()->back().two_points_made = float_or_negative(value);
  } else if (attribute == "fg2a_per_g") {
    season()->back().two_points_attempt = float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    season()->back().two_points_percentage = float_or_negative(value);
  } else if (attribute == "efg_pct") {
    season()->back().effective_field_goal_percentage = float_or_negative(value);
  } else if (attribute == "ft_per_g") {
    season()->back().free_throws_made = float_or_negative(value);
  } else if (attribute == "fta_per_g") {
    season()->back().free_throws_attempt = float_or_negative(value);
  } else if (attribute == "ft_pct") {
    season()->back().free_throws_percentage = float_or_negative(value);
  } else if (attribute == "orb_per_g") {
    season()->back().offensive_rebounds = float_or_negative(value);
  } else if (attribute == "drb_per_g") {
    season()->back().defensive_rebounds = float_or_negative(value);
  } else if (attribute == "trb_per_g") {
    season()->back().total_rebounds = float_or_negative(value);
  } else if (attribute == "ast_per_g") {
    season()->back().assists = float_or_negative(value);
  } else if (attribute == "stl_per_g") {
    season()->back().steals = float_or_negative(value);
  } else if (attribute == "blk_per_g") {
    season()->back().blocks = float_or_negative(value);
  } else if (attribute == "tov_per_g") {
    season()->back().turnovers = float_or_negative(value);
  } else if (attribute == "pf_per_g") {
    season()->back().personal_fouls = float_or_negative(value);
  } else if (attribute == "pts_per_g") {
    season()->back().points = float_or_negative(value);
  }
}

void PerGameAdapter::SetSeason() {
  season_ = &player()->career_info.per_game_seasons;
}

}  // namespace hoops