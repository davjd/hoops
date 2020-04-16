#ifndef SHOOTING_ADAPTER_H_
#define SHOOTING_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Shooting" table.
class ShootingAdapter
    : public virtual AttributeAdapterImpl<
          PlayerMetadata::CareerInformation::ShootingStatLine> {
 public:
  ShootingAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<
            PlayerMetadata::CareerInformation::ShootingStatLine>(
            mutable_player) {}
  ~ShootingAdapter() {}
  ShootingAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // SHOOTING_ADAPTER_H_