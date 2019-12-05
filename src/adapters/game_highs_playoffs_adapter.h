#ifndef GAME_HIGHS_PLAYOFFS_ADAPTER_H_
#define GAME_HIGHS_PLAYOFFS_ADAPTER_H_

#include "game_highs_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Game Highs" playoffs table.
class GameHighsPlayoffsAdapter : public virtual GameHighsAdapter {
 public:
  GameHighsPlayoffsAdapter(PlayerMetadata* mutable_player)
      : GameHighsAdapter(mutable_player) {}
  ~GameHighsPlayoffsAdapter() {}
  GameHighsPlayoffsAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // GAME_HIGHS_PLAYOFFS_ADAPTER_H_