#ifndef TOTALS_ADAPTER_H_
#define TOTALS_ADAPTER_H_

#include "per_game_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Totals" table.
class TotalsAdapter : public virtual PerGameAdapter {
 public:
  TotalsAdapter(PlayerMetadata* mutable_player)
      : PerGameAdapter(mutable_player) {}
  ~TotalsAdapter() {}
  TotalsAdapter() = default;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PER_GAME_ADAPTER_H_