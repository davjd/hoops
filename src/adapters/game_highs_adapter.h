#ifndef GAME_HIGHS_ADAPTER_H_
#define GAME_HIGHS_ADAPTER_H_

#include "attribute_adapter_impl.h"
#include "player_metadata.h"

namespace hoops {

// Adapter for "Game Highs" table.
class GameHighsAdapter
    : public virtual AttributeAdapterImpl<
          PlayerMetadata::CareerInformation::GameHighsStatLine> {
 public:
  GameHighsAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapterImpl<
            PlayerMetadata::CareerInformation::GameHighsStatLine>(
            mutable_player) {}
  ~GameHighsAdapter() {}
  GameHighsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void SetSeason() override;
};

}  // namespace hoops

#endif  // GAME_HIGHS_ADAPTER_H_