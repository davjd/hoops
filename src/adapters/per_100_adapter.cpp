#include "per_100_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void Per100Adapter::AddAttribute(const std::string& attribute,
                                 std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
  if (player_->career_info.per_game_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.per_game_seasons.back().season = value;
  } else if (attribute == "age") {
    player_->career_info.per_game_seasons.back().age = int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.per_game_seasons.back().team = value;
  } else if (attribute == "lg_id") {
    player_->career_info.per_game_seasons.back().league = value;
  } else if (attribute == "pos") {
    std::cout << "modified value: " << value << "\n";
    player_->career_info.per_game_seasons.back().position = value;
  } else if (attribute == "g") {
    player_->career_info.per_game_seasons.back().stat_line.games =
        float_or_negative(value);
  } else if (attribute == "gs") {
    player_->career_info.per_game_seasons.back().stat_line.games_started =
        int_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.per_game_seasons.back().stat_line.minutes_played =
        float_or_negative(value);
  } else if (attribute == "fg_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.field_goals_made =
        float_or_negative(value);
  } else if (attribute == "fga_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "fg_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.field_goal_percentage = float_or_negative(value);
  } else if (attribute == "fg3_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.three_points_made =
        float_or_negative(value);
  } else if (attribute == "fg3a_per_poss") {
    player_->career_info.per_game_seasons.back()
        .stat_line.three_points_attempt = float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.three_points_percentage = float_or_negative(value);
  } else if (attribute == "fg2_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.two_points_made =
        float_or_negative(value);
  } else if (attribute == "fg2a_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.two_points_percentage = float_or_negative(value);
  } else if (attribute == "ft_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.free_throws_made =
        float_or_negative(value);
  } else if (attribute == "fta_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "ft_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.free_throws_percentage = float_or_negative(value);
  } else if (attribute == "orb_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "drb_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "trb_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.total_rebounds =
        float_or_negative(value);
  } else if (attribute == "ast_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.assists =
        float_or_negative(value);
  } else if (attribute == "stl_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.steals =
        float_or_negative(value);
  } else if (attribute == "blk_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.blocks =
        float_or_negative(value);
  } else if (attribute == "tov_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.turnovers =
        float_or_negative(value);
  } else if (attribute == "pf_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.personal_fouls =
        float_or_negative(value);
  } else if (attribute == "pts_per_poss") {
    player_->career_info.per_game_seasons.back().stat_line.points =
        float_or_negative(value);
  } else if (attribute == "off_rtg") {
    player_->career_info.per_game_seasons.back().stat_line.personal_fouls =
        float_or_negative(value);
  } else if (attribute == "def_rtg") {
    player_->career_info.per_game_seasons.back().stat_line.points =
        float_or_negative(value);
  }
}

void Per100Adapter::AddSeason() {
  player_->career_info.per_game_seasons.push_back(
      PlayerMetadata::CareerInformation::CareerSeason());
}

}  // namespace hoops