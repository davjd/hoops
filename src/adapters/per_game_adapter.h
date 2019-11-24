#ifndef PER_GAME_ADAPTER_H_
#define PER_GAME_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Per Game" table.
class PerGameAdapter : public AttributeAdapter {
 public:
  PerGameAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  PerGameAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // PER_GAME_ADAPTER_H_