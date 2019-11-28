#include "per_36_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void Per36Adapter::AddAttribute(const std::string& attribute,
                                std::string value) {
  if (player_->career_info.per_36_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.per_36_seasons.back().season_info.season = value;
  } else if (attribute == "age") {
    player_->career_info.per_36_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.per_36_seasons.back().season_info.team = value;
  } else if (attribute == "lg_id") {
    player_->career_info.per_36_seasons.back().season_info.league = value;
  } else if (attribute == "pos") {
    player_->career_info.per_36_seasons.back().season_info.position = value;
  } else if (attribute == "g") {
    player_->career_info.per_36_seasons.back().games = float_or_negative(value);
  } else if (attribute == "gs") {
    player_->career_info.per_36_seasons.back().games_started =
        int_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.per_36_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "fg_per_mp") {
    player_->career_info.per_36_seasons.back().field_goals_made =
        float_or_negative(value);
  } else if (attribute == "fga_per_mp") {
    player_->career_info.per_36_seasons.back().field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "fg_pct") {
    player_->career_info.per_36_seasons.back().field_goal_percentage =
        float_or_negative(value);
  } else if (attribute == "fg3_per_mp") {
    player_->career_info.per_36_seasons.back().three_points_made =
        float_or_negative(value);
  } else if (attribute == "fg3a_per_mp") {
    player_->career_info.per_36_seasons.back().three_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    player_->career_info.per_36_seasons.back().three_points_percentage =
        float_or_negative(value);
  } else if (attribute == "fg2_per_mp") {
    player_->career_info.per_36_seasons.back().two_points_made =
        float_or_negative(value);
  } else if (attribute == "fg2a_per_mp") {
    player_->career_info.per_36_seasons.back().two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    player_->career_info.per_36_seasons.back().two_points_percentage =
        float_or_negative(value);
  } else if (attribute == "ft_per_mp") {
    player_->career_info.per_36_seasons.back().free_throws_made =
        float_or_negative(value);
  } else if (attribute == "fta_per_mp") {
    player_->career_info.per_36_seasons.back().free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "ft_pct") {
    player_->career_info.per_36_seasons.back().free_throws_percentage =
        float_or_negative(value);
  } else if (attribute == "orb_per_mp") {
    player_->career_info.per_36_seasons.back().offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "drb_per_mp") {
    player_->career_info.per_36_seasons.back().defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "trb_per_mp") {
    player_->career_info.per_36_seasons.back().total_rebounds =
        float_or_negative(value);
  } else if (attribute == "ast_per_mp") {
    player_->career_info.per_36_seasons.back().assists =
        float_or_negative(value);
  } else if (attribute == "stl_per_mp") {
    player_->career_info.per_36_seasons.back().steals =
        float_or_negative(value);
  } else if (attribute == "blk_per_mp") {
    player_->career_info.per_36_seasons.back().blocks =
        float_or_negative(value);
  } else if (attribute == "tov_per_mp") {
    player_->career_info.per_36_seasons.back().turnovers =
        float_or_negative(value);
  } else if (attribute == "pf_per_mp") {
    player_->career_info.per_36_seasons.back().personal_fouls =
        float_or_negative(value);
  } else if (attribute == "pts_per_mp") {
    player_->career_info.per_36_seasons.back().points =
        float_or_negative(value);
  }
}

void Per36Adapter::AddSeason() {
  player_->career_info.per_36_seasons.push_back(
      PlayerMetadata::CareerInformation::Per36StatLine());
}

}  // namespace hoops