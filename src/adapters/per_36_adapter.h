#ifndef PER_36_ADAPTER_H_
#define PER_36_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Per Game" table.
class Per36Adapter : public virtual AttributeAdapter {
 public:
  Per36Adapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  ~Per36Adapter() {}
  Per36Adapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // PER_36_ADAPTER_H_