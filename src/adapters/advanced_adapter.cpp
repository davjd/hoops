#include "advanced_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void AdvancedAdapter::AddAttribute(const std::string& attribute,
                                   std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
  if (player_->career_info.advanced_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.advanced_seasons.back().season_info.season = value;
  } else if (attribute == "age") {
    player_->career_info.advanced_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.advanced_seasons.back().season_info.team = value;
  } else if (attribute == "lg_id") {
    player_->career_info.advanced_seasons.back().season_info.league = value;
  } else if (attribute == "pos") {
    player_->career_info.advanced_seasons.back().season_info.position = value;
  } else if (attribute == "g") {
    player_->career_info.advanced_seasons.back().games =
        int_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.advanced_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "per") {
    player_->career_info.advanced_seasons.back().player_effiency_rating =
        float_or_negative(value);
  } else if (attribute == "ts_pct") {
    player_->career_info.advanced_seasons.back().true_shooting_percentage =
        float_or_negative(value);
  } else if (attribute == "fg3a_per_fga_pct") {
    player_->career_info.advanced_seasons.back().three_points_attempt_rate =
        float_or_negative(value);
  } else if (attribute == "fta_per_fga_pct") {
    player_->career_info.advanced_seasons.back().free_throws_attempt_rate =
        float_or_negative(value);
  } else if (attribute == "orb_pct") {
    player_->career_info.advanced_seasons.back().offensive_rebounds_percentage =
        float_or_negative(value);
  } else if (attribute == "drb_pct") {
    player_->career_info.advanced_seasons.back().defensive_rebounds_percentage =
        float_or_negative(value);
  } else if (attribute == "trb_pct") {
    player_->career_info.advanced_seasons.back().total_rebounds_percentage =
        float_or_negative(value);
  } else if (attribute == "ast_pct") {
    player_->career_info.advanced_seasons.back().assists_percentage =
        float_or_negative(value);
  } else if (attribute == "stl_pct") {
    player_->career_info.advanced_seasons.back().steals_percentage =
        float_or_negative(value);
  } else if (attribute == "blk_pct") {
    player_->career_info.advanced_seasons.back().blocks_percentage =
        float_or_negative(value);
  } else if (attribute == "tov_pct") {
    player_->career_info.advanced_seasons.back().turnovers_percentage =
        float_or_negative(value);
  } else if (attribute == "usg_pct") {
    player_->career_info.advanced_seasons.back().usage_percentage =
        float_or_negative(value);
  } else if (attribute == "ows") {
    player_->career_info.advanced_seasons.back().offensive_win_shares =
        float_or_negative(value);
  } else if (attribute == "dws") {
    player_->career_info.advanced_seasons.back().defensive_win_shares =
        float_or_negative(value);
  } else if (attribute == "ws") {
    player_->career_info.advanced_seasons.back().win_shares =
        float_or_negative(value);
  } else if (attribute == "ws_per_48") {
    player_->career_info.advanced_seasons.back().win_shares_per_48 =
        float_or_negative(value);
  } else if (attribute == "obpm") {
    player_->career_info.advanced_seasons.back().obpm =
        float_or_negative(value);
  } else if (attribute == "dbpm") {
    player_->career_info.advanced_seasons.back().dbpm =
        float_or_negative(value);
  } else if (attribute == "bpm") {
    player_->career_info.advanced_seasons.back().bpm = float_or_negative(value);
  } else if (attribute == "vorp") {
    player_->career_info.advanced_seasons.back().vorp =
        float_or_negative(value);
  }
}

void AdvancedAdapter::AddSeason() {
  player_->career_info.advanced_seasons.push_back(
      PlayerMetadata::CareerInformation::AdvancedStatLine());
}

}  // namespace hoops