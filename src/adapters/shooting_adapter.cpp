#include "shooting_adapter.h"

#include <iostream>
#include "util.h"

namespace hoops {

void ShootingAdapter::AddAttribute(const std::string& attribute,
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
  } else if (attribute == "mp") {
    season()->back().minutes_played = float_or_negative(value);
  } else if (attribute == "fg_pct") {
    season()->back().field_goals_percentage = float_or_negative(value);
  } else if (attribute == "avg_dist") {
    season()->back().average_distance = float_or_negative(value);
  } else if (attribute == "fg2a_pct_fga") {
    season()->back().two_points_number_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_00_03") {
    season()->back().distance_0_3_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_03_10") {
    season()->back().distance_3_10_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_10_16") {
    season()->back().distance_10_16_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_16_xx") {
    season()->back().distance_16_percentage = float_or_negative(value);
  } else if (attribute == "fg3a_pct_fga") {
    season()->back().three_points_number_percentage = float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    season()->back().two_points_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_00_03") {
    season()->back().distance_0_3_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_03_10") {
    season()->back().distance_3_10_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_10_16") {
    season()->back().distance_10_16_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_16_xx-dum") {
    season()->back().distance_16_field_percentage = float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    season()->back().three_points_field_percentage = float_or_negative(value);
  } else if (attribute == "fg2_pct_ast") {
    season()->back().two_points_assisted = float_or_negative(value);
  } else if (attribute == "pct_fg2_dunk") {
    season()->back().dunks_number_percentage = float_or_negative(value);
  } else if (attribute == "fg2_dunk") {
    season()->back().dunks_made = float_or_negative(value);
  } else if (attribute == "fg3_pct_ast") {
    season()->back().three_points_assisted = float_or_negative(value);
  } else if (attribute == "pct_fg3a_corner") {
    season()->back().corner_three_attempt_percentage = float_or_negative(value);
  } else if (attribute == "fg3_pct_corner") {
    season()->back().corner_three_field_percentage = float_or_negative(value);
  } else if (attribute == "fg3a_heave") {
    season()->back().heave_attempt = float_or_negative(value);
  } else if (attribute == "fg3_heave") {
    season()->back().heave_made = float_or_negative(value);
  }
}

void ShootingAdapter::SetSeason() {
  season_ = &player()->career_info.shooting_seasons;
}

}  // namespace hoops