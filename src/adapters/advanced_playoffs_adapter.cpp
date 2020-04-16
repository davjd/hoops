#include "advanced_playoffs_adapter.h"

#include "player_metadata.h"
#include "util.h"

namespace hoops {

void AdvancedPlayoffsAdapter::SetSeason() {
  season_ = &player()->career_info.advanced_playoff_seasons;
}

}  // namespace hoops