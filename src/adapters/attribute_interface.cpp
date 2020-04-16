#include "attribute_interface.h"

namespace hoops {

void AttributeInterface::SetPlayer(PlayerMetadata* mutable_player) {
  player_ = mutable_player;
}

PlayerMetadata* AttributeInterface::player() { return player_; }

}  // namespace hoops