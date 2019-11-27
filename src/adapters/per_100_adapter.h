#ifndef PER_100_ADAPTER_H_
#define PER_100_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Per 100 Poss" table.
class Per100Adapter : public virtual AttributeAdapter {
 public:
  Per100Adapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
      ~Per100Adapter() {}
  Per100Adapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // PER_100_ADAPTER_H_