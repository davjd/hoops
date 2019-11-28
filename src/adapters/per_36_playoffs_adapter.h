#ifndef PER_36_PLAYOFFS_ADAPTER_H_
#define PER_36_PLAYOFFS_ADAPTER_H_

#include "per_36_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Per 36" playoffs table.
class Per36PlayoffsAdapter : public virtual Per36Adapter {
 public:
  Per36PlayoffsAdapter(PlayerMetadata* mutable_player)
      : Per36Adapter(mutable_player) {}
  ~Per36PlayoffsAdapter() {}
  Per36PlayoffsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // PER_36_PLAYOFFS_ADAPTER_H_