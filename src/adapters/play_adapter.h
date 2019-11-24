#ifndef PLAY_ADAPTER_H_
#define PLAY_ADAPTER_H_

#include "attribute_adapter.h"

namespace hoops {

class PlayerMetadata;

// Adapter for "Play-by-Play" table.
class PlayerAdapter : public AttributeAdapter {
 public:
  PlayerAdapter(PlayerMetadata* mutable_player)
      : AttributeAdapter(mutable_player) {}
  PlayerAdapter() = default;
  void AddAttribute(const std::string& attribute, std::string value) override;
  void AddSeason() override;
};

}  // namespace hoops

#endif  // PLAY_ADAPTER_H_