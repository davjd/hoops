#include "per_36_playoffs_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void Per36PlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.per_36_playoff_seasons;
}

}  // namespace hoops