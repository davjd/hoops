#include "shooting_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void ShootingAdapter::AddAttribute(const std::string& attribute,
                                   std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
  if (player_->career_info.per_game_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.per_game_seasons.back().season_info.season = value;
  } else if (attribute == "age") {
    player_->career_info.per_game_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.per_game_seasons.back().season_info.team = value;
  } else if (attribute == "lg_id") {
    player_->career_info.per_game_seasons.back().season_info.league = value;
  } else if (attribute == "pos") {
    player_->career_info.per_game_seasons.back().season_info.position = value;
  } else if (attribute == "g") {
    player_->career_info.per_game_seasons.back().games =
        float_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.per_game_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "fg_pct") {
    player_->career_info.per_game_seasons.back().field_goals_made =
        float_or_negative(value);
  } else if (attribute == "avg_dist") {
    player_->career_info.per_game_seasons.back().field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "fg2a_pct_fga") {
    player_->career_info.per_game_seasons.back().field_goal_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_fga_00_03") {
    player_->career_info.per_game_seasons.back().three_points_made =
        float_or_negative(value);
  } else if (attribute == "pct_fga_03_10") {
    player_->career_info.per_game_seasons.back().three_points_attempt =
        float_or_negative(value);
  } else if (attribute == "pct_fga_10_16") {
    player_->career_info.per_game_seasons.back().three_points_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_fga_16_xx") {
    player_->career_info.per_game_seasons.back().two_points_made =
        float_or_negative(value);
  } else if (attribute == "fg3a_pct_fga") {
    player_->career_info.per_game_seasons.back().two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    player_->career_info.per_game_seasons.back().two_points_percentage =
        float_or_negative(value);
  } else if (attribute == "fg_pct_00_03") {
    player_->career_info.per_game_seasons.back().free_throws_made =
        float_or_negative(value);
  } else if (attribute == "fg_pct_03_10") {
    player_->career_info.per_game_seasons.back().free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "fg_pct_10_16") {
    player_->career_info.per_game_seasons.back().free_throws_percentage =
        float_or_negative(value);
  } else if (attribute == "fg_pct_16_xx-dum") {
    player_->career_info.per_game_seasons.back().offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    player_->career_info.per_game_seasons.back().defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "fg2_pct_ast") {
    player_->career_info.per_game_seasons.back().total_rebounds =
        float_or_negative(value);
  } else if (attribute == "pct_fg2_dunk") {
    player_->career_info.per_game_seasons.back().assists =
        float_or_negative(value);
  } else if (attribute == "fg2_dunk") {
    player_->career_info.per_game_seasons.back().steals =
        float_or_negative(value);
  } else if (attribute == "fg3_pct_ast") {
    player_->career_info.per_game_seasons.back().blocks =
        float_or_negative(value);
  } else if (attribute == "pct_fg3a_corner") {
    player_->career_info.per_game_seasons.back().turnovers =
        float_or_negative(value);
  } else if (attribute == "fg3_pct_corner") {
    player_->career_info.per_game_seasons.back().personal_fouls =
        float_or_negative(value);
  } else if (attribute == "fg3a_heave") {
    player_->career_info.per_game_seasons.back().points =
        float_or_negative(value);
  } else if (attribute == "fg3_heave") {
    player_->career_info.per_game_seasons.back().personal_fouls =
        float_or_negative(value);
  }
}

void ShootingAdapter::AddSeason() {
  player_->career_info.per_game_seasons.push_back(
      PlayerMetadata::CareerInformation::PerGameStatLine());
}

}  // namespace hoops