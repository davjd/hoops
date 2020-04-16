#include "totals_all_star_adapter.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

void TotalsAllStarAdapter::SetSeason() {
  season_ = &player()->career_info.totals_all_star_seasons;
}

}  // namespace hoops