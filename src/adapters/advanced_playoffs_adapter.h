#ifndef ADVANCED_PLAYOFFS_ADAPTER_H_
#define ADVANCED_PLAYOFFS_ADAPTER_H_

#include "advanced_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Advanced" playoffs table.
class AdvancedPlayoffsAdapter : public virtual AdvancedAdapter {
 public:
  AdvancedPlayoffsAdapter(PlayerMetadata* mutable_player)
      : AdvancedAdapter(mutable_player) {}
  ~AdvancedPlayoffsAdapter() {}
  AdvancedPlayoffsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // ADVANCED_PLAYOFFS_ADAPTER_H_