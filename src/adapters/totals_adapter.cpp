#include "totals_adapter.h"

#include "player_metadata.h"

#include <iostream>

namespace hoops {

void TotalsAdapter::SetSeason() {
  season_ = &player()->career_info.totals_seasons;
}

}  // namespace hoops