#ifndef TOTALS_ALL_STAR_ADAPTER_H_
#define TOTALS_ALL_STAR_ADAPTER_H_

#include "totals_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Totals" all-star table.
class TotalsAllStarAdapter : public virtual TotalsAdapter {
 public:
  TotalsAllStarAdapter(PlayerMetadata* mutable_player)
      : TotalsAdapter(mutable_player) {}
  ~TotalsAllStarAdapter() {}
  TotalsAllStarAdapter() = default;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // TOTALS_ALL_STAR_ADAPTER_H_