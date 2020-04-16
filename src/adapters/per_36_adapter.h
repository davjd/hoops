#ifndef PER_36_ADAPTER_H_
#define PER_36_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Per 36" table.
class Per36Adapter : public virtual AttributeAdapterImpl<
                         PlayerMetadata::CareerInformation::Per36StatLine> {
 public:
  Per36Adapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<PlayerMetadata::CareerInformation::Per36StatLine>(
            mutable_player) {}
  ~Per36Adapter() {}
  Per36Adapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PER_36_ADAPTER_H_