#include "per_100_playoffs_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void Per100PlayoffsAdapter::AddAttribute(const std::string& attribute,
                                         std::string value) {
  // TODO: Update this adapter with correct member variables (including last
  // two).
  if (player_->career_info.per_100_playoff_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.per_100_playoff_seasons.back().season_info.season =
        value;
  } else if (attribute == "age") {
    player_->career_info.per_100_playoff_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.per_100_playoff_seasons.back().season_info.team =
        value;
  } else if (attribute == "lg_id") {
    player_->career_info.per_100_playoff_seasons.back().season_info.league =
        value;
  } else if (attribute == "pos") {
    player_->career_info.per_100_playoff_seasons.back().season_info.position =
        value;
  } else if (attribute == "g") {
    player_->career_info.per_100_playoff_seasons.back().games =
        float_or_negative(value);
  } else if (attribute == "gs") {
    player_->career_info.per_100_playoff_seasons.back().games_started =
        int_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.per_100_playoff_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "fg_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().field_goals_made =
        float_or_negative(value);
  } else if (attribute == "fga_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "fg_pct") {
    player_->career_info.per_100_playoff_seasons.back().field_goal_percentage =
        float_or_negative(value);
  } else if (attribute == "fg3_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().three_points_made =
        float_or_negative(value);
  } else if (attribute == "fg3a_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().three_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    player_->career_info.per_100_playoff_seasons.back()
        .three_points_percentage = float_or_negative(value);
  } else if (attribute == "fg2_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().two_points_made =
        float_or_negative(value);
  } else if (attribute == "fg2a_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    player_->career_info.per_100_playoff_seasons.back().two_points_percentage =
        float_or_negative(value);
  } else if (attribute == "ft_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().free_throws_made =
        float_or_negative(value);
  } else if (attribute == "fta_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "ft_pct") {
    player_->career_info.per_100_playoff_seasons.back().free_throws_percentage =
        float_or_negative(value);
  } else if (attribute == "orb_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "drb_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "trb_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().total_rebounds =
        float_or_negative(value);
  } else if (attribute == "ast_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().assists =
        float_or_negative(value);
  } else if (attribute == "stl_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().steals =
        float_or_negative(value);
  } else if (attribute == "blk_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().blocks =
        float_or_negative(value);
  } else if (attribute == "tov_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().turnovers =
        float_or_negative(value);
  } else if (attribute == "pf_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().personal_fouls =
        float_or_negative(value);
  } else if (attribute == "pts_per_poss") {
    player_->career_info.per_100_playoff_seasons.back().points =
        float_or_negative(value);
  } else if (attribute == "off_rtg") {
    player_->career_info.per_100_playoff_seasons.back().offensive_rating =
        float_or_negative(value);
  } else if (attribute == "def_rtg") {
    player_->career_info.per_100_playoff_seasons.back().defensive_rating =
        float_or_negative(value);
  }
}

void Per100PlayoffsAdapter::AddSeason() {
  player_->career_info.per_100_playoff_seasons.push_back(
      PlayerMetadata::CareerInformation::Per100StatLine());
}

}  // namespace hoops