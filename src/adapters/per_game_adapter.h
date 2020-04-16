#ifndef PER_GAME_ADAPTER_H_
#define PER_GAME_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Per Game" table.
class PerGameAdapter : public virtual AttributeAdapterImpl<
                           PlayerMetadata::CareerInformation::PerGameStatLine> {
 public:
  PerGameAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<
            PlayerMetadata::CareerInformation::PerGameStatLine>(
            mutable_player) {}
  ~PerGameAdapter() {}
  PerGameAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PER_GAME_ADAPTER_H_