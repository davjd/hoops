#include "totals_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void TotalsAdapter::AddAttribute(const std::string& attribute,
                                 std::string value) {
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
  } else if (attribute == "gs") {
    player_->career_info.per_game_seasons.back().games_started =
        int_or_negative(value);
  } else if (attribute == "mp") {
    player_->career_info.per_game_seasons.back().minutes_played =
        float_or_negative(value);
  } else if (attribute == "fg") {
    player_->career_info.per_game_seasons.back().field_goals_made =
        float_or_negative(value);
  } else if (attribute == "fga") {
    player_->career_info.per_game_seasons.back().field_goals_attempt =
        float_or_negative(value);
  } else if (attribute == "fg_pct") {
    player_->career_info.per_game_seasons.back().field_goal_percentage =
        float_or_negative(value);
  } else if (attribute == "fg3") {
    player_->career_info.per_game_seasons.back().three_points_made =
        float_or_negative(value);
  } else if (attribute == "fg3a") {
    player_->career_info.per_game_seasons.back().three_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg3_pct") {
    player_->career_info.per_game_seasons.back().three_points_percentage =
        float_or_negative(value);
  } else if (attribute == "fg2") {
    player_->career_info.per_game_seasons.back().two_points_made =
        float_or_negative(value);
  } else if (attribute == "fg2a") {
    player_->career_info.per_game_seasons.back().two_points_attempt =
        float_or_negative(value);
  } else if (attribute == "fg2_pct") {
    player_->career_info.per_game_seasons.back().two_points_percentage =
        float_or_negative(value);
  } else if (attribute == "efg_pct") {
    player_->career_info.per_game_seasons.back()
        .effective_field_goal_percentage = float_or_negative(value);
  } else if (attribute == "ft") {
    player_->career_info.per_game_seasons.back().free_throws_made =
        float_or_negative(value);
  } else if (attribute == "fta") {
    player_->career_info.per_game_seasons.back().free_throws_attempt =
        float_or_negative(value);
  } else if (attribute == "ft_pct") {
    player_->career_info.per_game_seasons.back().free_throws_percentage =
        float_or_negative(value);
  } else if (attribute == "orb") {
    player_->career_info.per_game_seasons.back().offensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "drb") {
    player_->career_info.per_game_seasons.back().defensive_rebounds =
        float_or_negative(value);
  } else if (attribute == "trb") {
    player_->career_info.per_game_seasons.back().total_rebounds =
        float_or_negative(value);
  } else if (attribute == "ast") {
    player_->career_info.per_game_seasons.back().assists =
        float_or_negative(value);
  } else if (attribute == "stl") {
    player_->career_info.per_game_seasons.back().steals =
        float_or_negative(value);
  } else if (attribute == "blk") {
    player_->career_info.per_game_seasons.back().blocks =
        float_or_negative(value);
  } else if (attribute == "tov") {
    player_->career_info.per_game_seasons.back().turnovers =
        float_or_negative(value);
  } else if (attribute == "pf") {
    player_->career_info.per_game_seasons.back().personal_fouls =
        float_or_negative(value);
  } else if (attribute == "pts") {
    player_->career_info.per_game_seasons.back().points =
        float_or_negative(value);
  }
}

void TotalsAdapter::AddSeason() {
  player_->career_info.per_game_seasons.push_back(
      PlayerMetadata::CareerInformation::PerGameStatLine());
}

}  // namespace hoops