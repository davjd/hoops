#include "attribute_adapter.h"

namespace hoops {

void AttributeAdapter::SetPlayer(PlayerMetadata* mutable_player) {
  player_ = mutable_player;
}

}  // namespace hoops