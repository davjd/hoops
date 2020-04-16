#include "advanced_adapter.h"

#include <iostream>
#include "util.h"

namespace hoops {

void AdvancedAdapter::AddAttribute(const std::string& attribute,
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
    season()->back().games = int_or_negative(value);
  } else if (attribute == "mp") {
    season()->back().minutes_played = float_or_negative(value);
  } else if (attribute == "per") {
    season()->back().player_effiency_rating = float_or_negative(value);
  } else if (attribute == "ts_pct") {
    season()->back().true_shooting_percentage = float_or_negative(value);
  } else if (attribute == "fg3a_per_fga_pct") {
    season()->back().three_points_attempt_rate = float_or_negative(value);
  } else if (attribute == "fta_per_fga_pct") {
    season()->back().free_throws_attempt_rate = float_or_negative(value);
  } else if (attribute == "orb_pct") {
    season()->back().offensive_rebounds_percentage = float_or_negative(value);
  } else if (attribute == "drb_pct") {
    season()->back().defensive_rebounds_percentage = float_or_negative(value);
  } else if (attribute == "trb_pct") {
    season()->back().total_rebounds_percentage = float_or_negative(value);
  } else if (attribute == "ast_pct") {
    season()->back().assists_percentage = float_or_negative(value);
  } else if (attribute == "stl_pct") {
    season()->back().steals_percentage = float_or_negative(value);
  } else if (attribute == "blk_pct") {
    season()->back().blocks_percentage = float_or_negative(value);
  } else if (attribute == "tov_pct") {
    season()->back().turnovers_percentage = float_or_negative(value);
  } else if (attribute == "usg_pct") {
    season()->back().usage_percentage = float_or_negative(value);
  } else if (attribute == "ows") {
    season()->back().offensive_win_shares = float_or_negative(value);
  } else if (attribute == "dws") {
    season()->back().defensive_win_shares = float_or_negative(value);
  } else if (attribute == "ws") {
    season()->back().win_shares = float_or_negative(value);
  } else if (attribute == "ws_per_48") {
    season()->back().win_shares_per_48 = float_or_negative(value);
  } else if (attribute == "obpm") {
    season()->back().obpm = float_or_negative(value);
  } else if (attribute == "dbpm") {
    season()->back().dbpm = float_or_negative(value);
  } else if (attribute == "bpm") {
    season()->back().bpm = float_or_negative(value);
  } else if (attribute == "vorp") {
    season()->back().vorp = float_or_negative(value);
  }
}

void AdvancedAdapter::SetSeason() {
  season_ = &player()->career_info.advanced_seasons;
}

}  // namespace hoops
