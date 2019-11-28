#include "shooting_playoffs_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void ShootingPlayoffsAdapter::AddAttribute(const std::string& attribute,
                                           std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
  if (player_->career_info.shooting_playoff_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.shooting_playoff_seasons.back().season_info.season =
        value;
  } else if (attribute == "age") {
    player_->career_info.shooting_playoff_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.shooting_playoff_seasons.back().season_info.team =
        value;
  } else if (attribute == "lg_id") {
    player_->career_info.shooting_playoff_seasons.back().season_info.league =
        value;
  } else if (attribute == "pos") {
    player_->career_info.shooting_playoff_seasons.back().season_info.position =
        value;
  } else if (attribute == "g") {
    player_->career_info.shooting_playoff_seasons.back().games =
        float_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.shooting_playoff_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "fg_pct") {
    player_->career_info.shooting_playoff_seasons.back()
        .field_goals_percentage = float_or_negative(value);
  } else if (attribute == "avg_dist") {
    player_->career_info.shooting_playoff_seasons.back().average_distance =
        float_or_negative(value);
  } else if (attribute == "fg2a_pct_fga") {
    player_->career_info.shooting_playoff_seasons.back()
        .two_points_number_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_00_03") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_0_3_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_03_10") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_3_10_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_10_16") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_10_16_percentage = float_or_negative(value);
  } else if (attribute == "pct_fga_16_xx") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_16_percentage = float_or_negative(value);
  } else if (attribute == "fg3a_pct_fga") {
    player_->career_info.shooting_playoff_seasons.back()
        .three_points_number_percentage = float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    player_->career_info.shooting_playoff_seasons.back()
        .two_points_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_00_03") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_0_3_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_03_10") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_3_10_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_10_16") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_10_16_field_percentage = float_or_negative(value);
  } else if (attribute == "fg_pct_16_xx-dum") {
    player_->career_info.shooting_playoff_seasons.back()
        .distance_16_field_percentage = float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    player_->career_info.shooting_playoff_seasons.back()
        .three_points_field_percentage = float_or_negative(value);
  } else if (attribute == "fg2_pct_ast") {
    player_->career_info.shooting_playoff_seasons.back().two_points_assisted =
        float_or_negative(value);
  } else if (attribute == "pct_fg2_dunk") {
    player_->career_info.shooting_playoff_seasons.back()
        .dunks_number_percentage = float_or_negative(value);
  } else if (attribute == "fg2_dunk") {
    player_->career_info.shooting_playoff_seasons.back().dunks_made =
        float_or_negative(value);
  } else if (attribute == "fg3_pct_ast") {
    player_->career_info.shooting_playoff_seasons.back().three_points_assisted =
        float_or_negative(value);
  } else if (attribute == "pct_fg3a_corner") {
    player_->career_info.shooting_playoff_seasons.back()
        .corner_three_attempt_percentage = float_or_negative(value);
  } else if (attribute == "fg3_pct_corner") {
    player_->career_info.shooting_playoff_seasons.back()
        .corner_three_field_percentage = float_or_negative(value);
  } else if (attribute == "fg3a_heave") {
    player_->career_info.shooting_playoff_seasons.back().heave_attempt =
        float_or_negative(value);
  } else if (attribute == "fg3_heave") {
    player_->career_info.shooting_playoff_seasons.back().heave_made =
        float_or_negative(value);
  }
}

void ShootingPlayoffsAdapter::AddSeason() {
  player_->career_info.shooting_playoff_seasons.push_back(
      PlayerMetadata::CareerInformation::ShootingStatLine());
}

}  // namespace hoops