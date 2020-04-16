#include "totals_playoffs_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void TotalsPlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.totals_playoff_seasons;
}

}  // namespace hoops