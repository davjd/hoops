#include "per_game_playoffs_adapter.h"

#include "player_metadata.h"
#include "util.h"

namespace hoops {

void PerGamePlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.per_game_playoff_seasons;
}

}  // namespace hoops