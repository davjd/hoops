#ifndef TOTALS_ADAPTER_H_
#define TOTALS_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Totals" table.
class TotalsAdapter : public AttributeAdapter {
 public:
  TotalsAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  TotalsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // PER_GAME_ADAPTER_H_