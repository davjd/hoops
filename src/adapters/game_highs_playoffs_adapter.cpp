#include "game_highs_playoffs_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void GameHighsPlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.game_highs_playoff_seasons;
}

}  // namespace hoops