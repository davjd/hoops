#ifndef PER_100_PLAYOFFS_ADAPTER_H_
#define PER_100_PLAYOFFS_ADAPTER_H_

#include "per_100_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Per 100 Poss" table.
class Per100PlayoffsAdapter : public virtual Per100Adapter {
 public:
  Per100PlayoffsAdapter(PlayerMetadata* mutable_player)
      : Per100Adapter(mutable_player) {}
  ~Per100PlayoffsAdapter() {}
  Per100PlayoffsAdapter() = default;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PER_100_PLAYOFFS_ADAPTER_H_