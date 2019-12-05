#include "game_highs_playoffs_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void GameHighsPlayoffsAdapter::AddAttribute(const std::string& attribute,
                                            std::string value) {
  if (player_->career_info.game_highs_playoff_seasons.empty()) return;
  if (attribute == "Season") {
    player_->career_info.game_highs_playoff_seasons.back().season_info.season =
        value;
  } else if (attribute == "age") {
    player_->career_info.game_highs_playoff_seasons.back().season_info.age =
        int_or_negative(value);
  } else if (attribute == "team_id") {
    player_->career_info.game_highs_playoff_seasons.back().season_info.team =
        value;
  } else if (attribute == "lg_id") {
    player_->career_info.game_highs_playoff_seasons.back().season_info.league =
        value;
  } else if (attribute == "mp") {
    player_->career_info.game_highs_playoff_seasons.back().minutes_played =
        value;
  } else if (attribute == "fg") {
    player_->career_info.game_highs_playoff_seasons.back().field_goals_made =
        int_or_negative(value);
  } else if (attribute == "fga") {
    player_->career_info.game_highs_playoff_seasons.back().field_goals_attempt =
        int_or_negative(value);
  } else if (attribute == "fg3") {
    player_->career_info.game_highs_playoff_seasons.back().three_points_made =
        int_or_negative(value);
  } else if (attribute == "fg3a") {
    player_->career_info.game_highs_playoff_seasons.back()
        .three_points_attempt = int_or_negative(value);
  } else if (attribute == "fg2") {
    player_->career_info.game_highs_playoff_seasons.back().two_points_made =
        int_or_negative(value);
  } else if (attribute == "fg2a") {
    player_->career_info.game_highs_playoff_seasons.back().two_points_attempt =
        int_or_negative(value);
  } else if (attribute == "ft") {
    player_->career_info.game_highs_playoff_seasons.back().free_throws_made =
        int_or_negative(value);
  } else if (attribute == "fta") {
    player_->career_info.game_highs_playoff_seasons.back().free_throws_attempt =
        int_or_negative(value);
  } else if (attribute == "orb") {
    player_->career_info.game_highs_playoff_seasons.back().offensive_rebounds =
        int_or_negative(value);
  } else if (attribute == "drb") {
    player_->career_info.game_highs_playoff_seasons.back().defensive_rebounds =
        int_or_negative(value);
  } else if (attribute == "trb") {
    player_->career_info.game_highs_playoff_seasons.back().total_rebounds =
        int_or_negative(value);
  } else if (attribute == "ast") {
    player_->career_info.game_highs_playoff_seasons.back().assists =
        int_or_negative(value);
  } else if (attribute == "stl") {
    player_->career_info.game_highs_playoff_seasons.back().steals =
        int_or_negative(value);
  } else if (attribute == "blk") {
    player_->career_info.game_highs_playoff_seasons.back().blocks =
        int_or_negative(value);
  } else if (attribute == "tov") {
    player_->career_info.game_highs_playoff_seasons.back().turnovers =
        int_or_negative(value);
  } else if (attribute == "pf") {
    player_->career_info.game_highs_playoff_seasons.back().personal_fouls =
        int_or_negative(value);
  } else if (attribute == "pts") {
    player_->career_info.game_highs_playoff_seasons.back().points =
        int_or_negative(value);
  } else if (attribute == "game_score") {
    player_->career_info.game_highs_playoff_seasons.back().game_score =
        float_or_negative(value);
  }
}

void GameHighsPlayoffsAdapter::AddSeason() {
  player_->career_info.game_highs_playoff_seasons.push_back(
      PlayerMetadata::CareerInformation::GameHighsStatLine());
}

}  // namespace hoops