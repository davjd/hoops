#ifndef PLAY_PLAYOFFS_ADAPTER_H_
#define PLAY_PLAYOFFS_ADAPTER_H_

#include "play_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Play-by-Play" playoffs table.
class PlayPlayoffsAdapter : public virtual PlayAdapter {
 public:
  PlayPlayoffsAdapter(PlayerMetadata* mutable_player)
      : PlayAdapter(mutable_player) {}
  ~PlayPlayoffsAdapter() {}
  PlayPlayoffsAdapter() = default;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PLAY_PLAYOFFS_ADAPTER_H_