#include "advanced_playoffs_adapter.h"

#include "player_metadata.h"

namespace hoops {

void AdvancedPlayoffsAdapter::AddSeason() {
  player_->career_info.advanced_playoff_seasons.push_back(
      PlayerMetadata::CareerInformation::AdvancedStatLine());
}

}  // namespace hoops