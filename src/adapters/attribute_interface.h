#ifndef ATTRIBUTE_INTERFACE_H_
#define ATTRIBUTE_INTERFACE_H_

#include <list>
#include <string>

// Updated attribute adapter with interface.

namespace hoops {

class PlayerMetadata;

class AttributeInterface {
 public:
  AttributeInterface(PlayerMetadata* mutable_player)
      : player_(mutable_player) {}
  AttributeInterface() = default;
  virtual ~AttributeInterface() {}

  // Given an attribute, we'll modify the season's attribute with the given
  // value. NOTE: AddSeason() call is needed before using this method.
  virtual void AddAttribute(const std::string& attribute,
                            std::string value) = 0;

  // Inserts new season container which will then be modified by the adapter.
  // NOTE: Needs to be called before modifying attributes.
  virtual void AddSeason() = 0;

  // The player object that will be modified by this adapter.
  // Probably won't be needed.
  void SetPlayer(PlayerMetadata* mutable_player);

  virtual void SetSeason() = 0;

  PlayerMetadata* player();

 protected:
  PlayerMetadata* player_;
};

}  // namespace hoops

#endif  // ATTRIBUTE_INTERFACE_H_