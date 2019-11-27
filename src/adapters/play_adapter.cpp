#include "play_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void PlayerAdapter::AddAttribute(const std::string& attribute,
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
  } else if (attribute == "pct_1") {
    player_->career_info.per_game_seasons.back().field_goals_made =
        float_or_negative(value);
  } else if (attribute == "pct_2") {
    player_->career_info.per_game_seasons.back().field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "pct_3") {
    player_->career_info.per_game_seasons.back().field_goal_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_4") {
    player_->career_info.per_game_seasons.back().three_points_made =
        float_or_negative(value);
  } else if (attribute == "pct_5") {
    player_->career_info.per_game_seasons.back().three_points_attempt =
        float_or_negative(value);
  } else if (attribute == "plus_minus_on") {
    player_->career_info.per_game_seasons.back().three_points_percentage =
        float_or_negative(value);
  } else if (attribute == "plus_minus_net") {
    player_->career_info.per_game_seasons.back().two_points_made =
        float_or_negative(value);
  } else if (attribute == "tov_bad_pass") {
    player_->career_info.per_game_seasons.back().two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "tov_lost_ball") {
    player_->career_info.per_game_seasons.back().two_points_percentage =
        float_or_negative(value);
  } else if (attribute == "fouls_shooting") {
    player_->career_info.per_game_seasons.back().free_throws_made =
        float_or_negative(value);
  } else if (attribute == "fouls_offensive") {
    player_->career_info.per_game_seasons.back().free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "drawn_shooting") {
    player_->career_info.per_game_seasons.back().free_throws_percentage =
        float_or_negative(value);
  } else if (attribute == "drawn_offensive") {
    player_->career_info.per_game_seasons.back().offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "astd_pts") {
    player_->career_info.per_game_seasons.back().defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "and1s") {
    player_->career_info.per_game_seasons.back().total_rebounds =
        float_or_negative(value);
  } else if (attribute == "own_shots_blk") {
    player_->career_info.per_game_seasons.back().assists =
        float_or_negative(value);
  }
}

void PlayerAdapter::AddSeason() {
  player_->career_info.per_game_seasons.push_back(
      PlayerMetadata::CareerInformation::PerGameStatLine());
}

}  // namespace hoops