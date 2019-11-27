#include "per_game_playoffs_adapter.h"

#include "player_metadata.h"

namespace hoops {

void PerGamePlayoffsAdapter::AddSeason() {
  player_->career_info.per_game_playoff_seasons.push_back(
      PlayerMetadata::CareerInformation::PerGameStatLine());
}

}  // namespace hoops