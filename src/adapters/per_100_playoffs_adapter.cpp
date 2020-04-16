#include "per_100_playoffs_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void Per100PlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.per_100_playoff_seasons;
}

}  // namespace hoops