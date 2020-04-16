#ifndef PER_100_ADAPTER_H_
#define PER_100_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Per 100 Poss" table.
class Per100Adapter : public virtual AttributeAdapterImpl<
                          PlayerMetadata::CareerInformation::Per100StatLine> {
 public:
  Per100Adapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<PlayerMetadata::CareerInformation::Per100StatLine>(
            mutable_player) {}
  ~Per100Adapter() {}
  Per100Adapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PER_100_ADAPTER_H_