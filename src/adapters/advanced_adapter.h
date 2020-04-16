#ifndef ADVANCED_ADAPTER_H_
#define ADVANCED_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Advanced" table.
class AdvancedAdapter
    : public virtual AttributeAdapterImpl<
          PlayerMetadata::CareerInformation::AdvancedStatLine> {
 public:
  AdvancedAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<
            PlayerMetadata::CareerInformation::AdvancedStatLine>(
            mutable_player) {}
  ~AdvancedAdapter() {}
  AdvancedAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // ADVANCED_ADAPTER_H_