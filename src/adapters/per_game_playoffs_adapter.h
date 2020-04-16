#ifndef PER_GAME_PLAYOFFS_ADAPTER_H_
#define PER_GAME_PLAYOFFS_ADAPTER_H_

#include "per_game_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Per Game" playoffs table.
class PerGamePlayoffsAdapter : public virtual PerGameAdapter {
 public:
  PerGamePlayoffsAdapter(PlayerMetadata* mutable_player)
      : PerGameAdapter(mutable_player) {}
  ~PerGamePlayoffsAdapter() {}
  PerGamePlayoffsAdapter() = default;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PER_GAME_PLAYOFFS_ADAPTER_H_