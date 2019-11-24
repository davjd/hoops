#include "advanced_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void AdvancedAdapter::AddAttribute(const std::string& attribute,
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
  } else if (attribute == "per") {
    player_->career_info.per_game_seasons.back().stat_line.field_goals_made =
        float_or_negative(value);
  } else if (attribute == "ts_pct") {
    player_->career_info.per_game_seasons.back().stat_line.field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "fg3a_per_fga_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.field_goal_percentage = float_or_negative(value);
  } else if (attribute == "fta_per_fga_pct") {
    player_->career_info.per_game_seasons.back().stat_line.three_points_made =
        float_or_negative(value);
  } else if (attribute == "orb_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.three_points_attempt = float_or_negative(value);
  } else if (attribute == "drb_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.three_points_percentage = float_or_negative(value);
  } else if (attribute == "trb_pct") {
    player_->career_info.per_game_seasons.back().stat_line.two_points_made =
        float_or_negative(value);
  } else if (attribute == "ast_pct") {
    player_->career_info.per_game_seasons.back().stat_line.two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "stl_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.two_points_percentage = float_or_negative(value);
  } else if (attribute == "blk_pct") {
    player_->career_info.per_game_seasons.back().stat_line.free_throws_made =
        float_or_negative(value);
  } else if (attribute == "tov_pct") {
    player_->career_info.per_game_seasons.back().stat_line.free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "usg_pct") {
    player_->career_info.per_game_seasons.back()
        .stat_line.free_throws_percentage = float_or_negative(value);
  } else if (attribute == "ws-dum") {
    player_->career_info.per_game_seasons.back().stat_line.offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "ows") {
    player_->career_info.per_game_seasons.back().stat_line.defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "dws") {
    player_->career_info.per_game_seasons.back().stat_line.total_rebounds =
        float_or_negative(value);
  } else if (attribute == "ws") {
    player_->career_info.per_game_seasons.back().stat_line.assists =
        float_or_negative(value);
  } else if (attribute == "ws_per_48") {
    player_->career_info.per_game_seasons.back().stat_line.steals =
        float_or_negative(value);
  } else if (attribute == "bpm-dum") {
    player_->career_info.per_game_seasons.back().stat_line.blocks =
        float_or_negative(value);
  } else if (attribute == "obpm") {
    player_->career_info.per_game_seasons.back().stat_line.turnovers =
        float_or_negative(value);
  } else if (attribute == "dbpm") {
    player_->career_info.per_game_seasons.back().stat_line.personal_fouls =
        float_or_negative(value);
  } else if (attribute == "bpm") {
    player_->career_info.per_game_seasons.back().stat_line.points =
        float_or_negative(value);
  } else if (attribute == "vorp") {
    player_->career_info.per_game_seasons.back().stat_line.personal_fouls =
        float_or_negative(value);
  }
}

void AdvancedAdapter::AddSeason() {
  player_->career_info.per_game_seasons.push_back(
      PlayerMetadata::CareerInformation::CareerSeason());
}

}  // namespace hoops