#include "shooting_playoffs_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void ShootingPlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.shooting_playoff_seasons;
}

}  // namespace hoops