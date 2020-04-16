#include "stats_adapters.h"

#include "adapters/advanced_adapter.h"
#include "adapters/advanced_playoffs_adapter.h"
#include "adapters/attribute_interface.h"
#include "adapters/game_highs_adapter.h"
#include "adapters/game_highs_playoffs_adapter.h"
#include "adapters/per_100_adapter.h"
#include "adapters/per_100_playoffs_adapter.h"
#include "adapters/per_36_adapter.h"
#include "adapters/per_36_playoffs_adapter.h"
#include "adapters/per_game_adapter.h"
#include "adapters/per_game_playoffs_adapter.h"
#include "adapters/play_adapter.h"
#include "adapters/play_playoffs_adapter.h"
#include "adapters/shooting_adapter.h"
#include "adapters/shooting_playoffs_adapter.h"
#include "adapters/totals_adapter.h"
#include "adapters/totals_all_star_adapter.h"
#include "adapters/totals_playoffs_adapter.h"

#include <memory>

namespace hoops {

// TODO: Game Highs and Playoff Game Highs doesn't have an adapter currently.
const std::array<std::pair<std::string, std::unique_ptr<AttributeInterface> >,
                 17>
    StatsAdapters::kAttributeAdapters = {
        {{"Per Game", std::make_unique<PerGameAdapter>()},
         {"Totals", std::make_unique<TotalsAdapter>()},
         {"Per 36 Minutes", std::make_unique<Per36Adapter>()},
         {"Per 100 Poss", std::make_unique<Per100Adapter>()},
         {"Advanced", std::make_unique<AdvancedAdapter>()},
         {"Shooting", std::make_unique<ShootingAdapter>()},
         {"Play-by-Play", std::make_unique<PlayAdapter>()},
         {"Playoffs Per Game", std::make_unique<PerGamePlayoffsAdapter>()},
         {"Playoffs Totals", std::make_unique<TotalsPlayoffsAdapter>()},
         {"Playoffs Per 36 Minutes", std::make_unique<Per36PlayoffsAdapter>()},
         {"Playoffs Per 100 Poss", std::make_unique<Per100PlayoffsAdapter>()},
         {"Playoffs Advanced", std::make_unique<AdvancedPlayoffsAdapter>()},
         {"Playoffs Shooting", std::make_unique<ShootingPlayoffsAdapter>()},
         {"Playoffs Play-by-Play", std::make_unique<PlayPlayoffsAdapter>()},
         {"All-Star Games", std::make_unique<TotalsAllStarAdapter>()},
         {"Game Highs", std::make_unique<GameHighsAdapter>()},
         {"Playoffs Game Highs",
          std::make_unique<GameHighsPlayoffsAdapter>()}}};

StatsAdapters::StatsAdapters() {}

StatsAdapters::~StatsAdapters() {}

AttributeInterface* StatsAdapters::GetAdapter(const std::string& adapter_name) {
  auto adapter =
      std::find_if(kAttributeAdapters.begin(), kAttributeAdapters.end(),
                   [&](auto& pair) { return pair.first == adapter_name; });
  if (adapter != std::end(kAttributeAdapters)) {
    return adapter->second.get();
  }
  return nullptr;
}

void StatsAdapters::SetPlayer(PlayerMetadata* mutable_player) {
  for (auto& adapter : kAttributeAdapters) {
    adapter.second->SetPlayer(mutable_player);
  }
}
}  // namespace hoops
