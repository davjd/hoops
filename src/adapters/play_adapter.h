#ifndef PLAY_ADAPTER_H_
#define PLAY_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Play-by-Play" table.
class PlayAdapter : public virtual AttributeAdapterImpl<
                        PlayerMetadata::CareerInformation::PlayStatLine> {
 public:
  PlayAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<PlayerMetadata::CareerInformation::PlayStatLine>(
            mutable_player) {}
  ~PlayAdapter() {}
  PlayAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // PLAY_ADAPTER_H_