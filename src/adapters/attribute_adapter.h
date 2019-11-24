#ifndef ATTRIBUTE_ADAPTER_H_
#define ATTRIBUTE_ADAPTER_H_

#include <string>

namespace hoops {

class PlayerMetadata;

class AttributeAdapter {
 public:
  AttributeAdapter(PlayerMetadata* mutable_player) : player_(mutable_player) {}
  AttributeAdapter() = default;
  virtual ~AttributeAdapter() {}

  // We'll be updating the 'tail' of the per_game linkedlist. Therefore the
  // client must insert the new season into list before adding attributes to
  // it. To ease this, AddSeason() is provided.
  virtual void AddAttribute(const std::string& attribute,
                            std::string value) = 0;

  // Should be called before adding attributes.
  virtual void AddSeason() = 0;

  // The player object that will be modified by this adapter.
  void SetPlayer(PlayerMetadata* mutable_player);

 protected:
  PlayerMetadata* player_;
};

}  // namespace hoops

#endif  // ATTRIBUTE_ADAPTER_H_