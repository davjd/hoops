#ifndef SHOOTING_ADAPTER_H_
#define SHOOTING_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Shooting" table.
class ShootingAdapter : public AttributeAdapter {
 public:
  ShootingAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  ShootingAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // SHOOTING_ADAPTER_H_