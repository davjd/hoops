#ifndef GAME_HIGHS_ADAPTER_H_
#define GAME_HIGHS_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Game Highs" table.
class GameHighsAdapter : public virtual AttributeAdapter {
 public:
  GameHighsAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  ~GameHighsAdapter() {}
  GameHighsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // GAME_HIGHS_ADAPTER_H_