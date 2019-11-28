#include "play_playoffs_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void PlayPlayoffsAdapter::AddAttribute(const std::string& attribute,
                                       std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
  if (player_->career_info.play_playoff_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.play_playoff_seasons.back().season_info.season = value;
  } else if (attribute == "age") {
    player_->career_info.play_playoff_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.play_playoff_seasons.back().season_info.team = value;
  } else if (attribute == "lg_id") {
    player_->career_info.play_playoff_seasons.back().season_info.league = value;
  } else if (attribute == "pos") {
    player_->career_info.play_playoff_seasons.back().season_info.position =
        value;
  } else if (attribute == "g") {
    player_->career_info.play_playoff_seasons.back().games =
        float_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.play_playoff_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "pct_1") {
    player_->career_info.play_playoff_seasons.back().point_guard_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_2") {
    player_->career_info.play_playoff_seasons.back().shooting_guard_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_3") {
    player_->career_info.play_playoff_seasons.back().small_forward_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_4") {
    player_->career_info.play_playoff_seasons.back().power_forward_percentage =
        float_or_negative(value);
  } else if (attribute == "pct_5") {
    player_->career_info.play_playoff_seasons.back().center_percentage =
        float_or_negative(value);
  } else if (attribute == "plus_minus_on") {
    player_->career_info.play_playoff_seasons.back().plus_minus_on =
        float_or_negative(value);
  } else if (attribute == "plus_minus_net") {
    player_->career_info.play_playoff_seasons.back().plus_minus_net =
        float_or_negative(value);
  } else if (attribute == "tov_bad_pass") {
    player_->career_info.play_playoff_seasons.back().bad_pass =
        float_or_negative(value);
  } else if (attribute == "tov_lost_ball") {
    player_->career_info.play_playoff_seasons.back().lost_ball =
        float_or_negative(value);
  } else if (attribute == "fouls_shooting") {
    player_->career_info.play_playoff_seasons.back().shooting_fouls =
        float_or_negative(value);
  } else if (attribute == "fouls_offensive") {
    player_->career_info.play_playoff_seasons.back().offensive_fouls =
        float_or_negative(value);
  } else if (attribute == "drawn_shooting") {
    player_->career_info.play_playoff_seasons.back().shooting_fouls_drawn =
        float_or_negative(value);
  } else if (attribute == "drawn_offensive") {
    player_->career_info.play_playoff_seasons.back().offensive_fouls_drawn =
        float_or_negative(value);
  } else if (attribute == "astd_pts") {
    player_->career_info.play_playoff_seasons.back().assisted_points =
        float_or_negative(value);
  } else if (attribute == "and1s") {
    player_->career_info.play_playoff_seasons.back().and_ones =
        float_or_negative(value);
  } else if (attribute == "own_shots_blk") {
    player_->career_info.play_playoff_seasons.back().blocked_attempt =
        float_or_negative(value);
  }
}

void PlayPlayoffsAdapter::AddSeason() {
  player_->career_info.play_playoff_seasons.push_back(
      PlayerMetadata::CareerInformation::PlayStatLine());
}

}  // namespace hoops