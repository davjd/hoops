#ifndef ATTRIBUTE_INTERFACE_H_
#define ATTRIBUTE_INTERFACE_H_

#include <list>
#include <string>

// Updated attribute adapter with interface.

namespace hoops {

class PlayerMetadata;

class AttributeInterface {
 public:
  AttributeInterface(PlayerMetadata* mutable_player) : player_(mutable_player) {}
  AttributeInterface() = default;
  virtual ~AttributeInterface() {}

  // Given an attribute, we'll modify the season's attribute with the given value.
  // NOTE: AddSeason() call is needed before using this method.
  virtual void AddAttribute(const std::string& attribute,
                            std::string value) = 0;
  // AddAttribute gets overwritten by each type of adapter.
  // e.g. all advanced will have share same AddAttribute defition.

  // Inserts new season container which will then be modified by the adapter.
  // NOTE: Needs to be called before modifying attributes.
  virtual void AddSeason() = 0;
  // -> season.addSeason(new T());

  // The player object that will be modified by this adapter.
  // Probably won't be needed.
  void SetPlayer(PlayerMetadata* mutable_player);

  virtual void SetSeason() = 0;

  PlayerMetadata* player();

  // SOOOO.. why do we need to abstract this interface?
  // - When we add a season, it's type needs to be abstracted so
  // we can then have modifiers inside an interface.
  // - We instead abstract the modifiers.

 protected:
  PlayerMetadata* player_;
  // std::list<T>* season_;
};

}  // namespace hoops

/*

class InterfaceForAdapter{
  virtual void AddAttribute(const std::string& attribute,
                            std::string value) = 0;
}

class PropertyInterface {
  // will only have the shared functions.
}

class PropertyManager<T> impl PropertyInterface{
  set_prop1() {
    property_ = 0;
  } .. etc.


  private:
  std::list<T>* property_;
}

*/

#endif  // ATTRIBUTE_INTERFACE_H_