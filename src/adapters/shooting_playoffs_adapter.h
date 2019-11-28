#ifndef SHOOTING_PLAYOFFS_ADAPTER_H_
#define SHOOTING_PLAYOFFS_ADAPTER_H_

#include "shooting_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Shooting" playoffs table.
class ShootingPlayoffsAdapter : public virtual ShootingAdapter {
 public:
  ShootingPlayoffsAdapter(PlayerMetadata* mutable_player)
      : ShootingAdapter(mutable_player) {}
  ~ShootingPlayoffsAdapter() {}
  ShootingPlayoffsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // SHOOTING_PLAYOFFS_ADAPTER_H_