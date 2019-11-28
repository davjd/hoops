#ifndef TOTALS_PLAYOFFS_ADAPTER_H_
#define TOTALS_PLAYOFFS_ADAPTER_H_

#include "totals_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Totals" playoffs table.
class TotalsPlayoffsAdapter : public virtual TotalsAdapter {
 public:
  TotalsPlayoffsAdapter(PlayerMetadata* mutable_player)
      : TotalsAdapter(mutable_player) {}
  ~TotalsPlayoffsAdapter() {}
  TotalsPlayoffsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // TOTALS_PLAYOFFS_ADAPTER_H_