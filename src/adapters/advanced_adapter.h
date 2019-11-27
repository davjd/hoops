#ifndef ADVANCED_ADAPTER_H_
#define ADVANCED_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Advanced" table.
class AdvancedAdapter : public virtual AttributeAdapter {
 public:
  AdvancedAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  ~AdvancedAdapter() {}
  AdvancedAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // ADVANCED_ADAPTER_H_