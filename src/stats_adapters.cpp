#include "stats_adapters.h"

#include "adapters/attribute_adapter.h"
#include "adapters/per_game_adapter.h"
#include "adapters/per_game_playoffs_adapter.h"

#include <memory>

namespace hoops {

const std::array<std::pair<std::string, std::unique_ptr<AttributeAdapter> >, 2>
    StatsAdapters::kAttributeAdapters = {
        {{"Per Game", std::make_unique<PerGameAdapter>()},
         {"Playoffs Per Game", std::make_unique<PerGamePlayoffsAdapter>()}}};

StatsAdapters::StatsAdapters() {}

StatsAdapters::~StatsAdapters() {}

AttributeAdapter* StatsAdapters::GetAdapter(const std::string& adapter_name) {
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
