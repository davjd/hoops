#include "play_playoffs_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void PlayPlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.play_playoff_seasons;
}

}  // namespace hoops