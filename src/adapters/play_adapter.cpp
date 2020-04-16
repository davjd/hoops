#include "play_adapter.h"

#include <iostream>
#include "util.h"

namespace hoops {

void PlayAdapter::AddAttribute(const std::string& attribute,
                               std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
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
  } else if (attribute == "pct_1") {
    season()->back().point_guard_percentage = float_or_negative(value);
  } else if (attribute == "pct_2") {
    season()->back().shooting_guard_percentage = float_or_negative(value);
  } else if (attribute == "pct_3") {
    season()->back().small_forward_percentage = float_or_negative(value);
  } else if (attribute == "pct_4") {
    season()->back().power_forward_percentage = float_or_negative(value);
  } else if (attribute == "pct_5") {
    season()->back().center_percentage = float_or_negative(value);
  } else if (attribute == "plus_minus_on") {
    season()->back().plus_minus_on = float_or_negative(value);
  } else if (attribute == "plus_minus_net") {
    season()->back().plus_minus_net = float_or_negative(value);
  } else if (attribute == "tov_bad_pass") {
    season()->back().bad_pass = float_or_negative(value);
  } else if (attribute == "tov_lost_ball") {
    season()->back().lost_ball = float_or_negative(value);
  } else if (attribute == "fouls_shooting") {
    season()->back().shooting_fouls = float_or_negative(value);
  } else if (attribute == "fouls_offensive") {
    season()->back().offensive_fouls = float_or_negative(value);
  } else if (attribute == "drawn_shooting") {
    season()->back().shooting_fouls_drawn = float_or_negative(value);
  } else if (attribute == "drawn_offensive") {
    season()->back().offensive_fouls_drawn = float_or_negative(value);
  } else if (attribute == "astd_pts") {
    season()->back().assisted_points = float_or_negative(value);
  } else if (attribute == "and1s") {
    season()->back().and_ones = float_or_negative(value);
  } else if (attribute == "own_shots_blk") {
    season()->back().blocked_attempt = float_or_negative(value);
  }
}

void PlayAdapter::SetSeason() { season_ = &player()->career_info.play_seasons; }

}  // namespace hoops