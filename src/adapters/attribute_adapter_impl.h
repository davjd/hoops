#ifndef ATTRIBUTE_ADAPTER_IMPL_H_
#define ATTRIBUTE_ADAPTER_IMPL_H_

#include <list>
#include <string>

#include "attribute_interface.h"

// Updated attribute adapter with interface.

namespace hoops {

class PlayerMetadata;

template <typename T>
class AttributeAdapterImpl : public AttributeInterface {
 public:
  using SeasonType = std::list<T>;
  AttributeAdapterImpl(PlayerMetadata* mutable_player);
  AttributeAdapterImpl();
  ~AttributeAdapterImpl();

  void AddAttribute(const std::string& attribute, std::string value) override;

  void AddSeason() override;

  SeasonType* season();

  // Set the season modified by the adapter.
  void set_season(SeasonType* season);

  // Set default behavior for the attribute.
  // Since the per_game adapter is the most used, we'll have that
  // as its season setter. However, this should be overwritten with
  // other adapters.
  void SetSeason() override;

  // SOOOO.. why do we need to abstract this interface?
  // - When we add a season, it's type needs to be abstracted so
  // we can then have modifiers inside an interface.
  // - We instead abstract the modifiers.

 protected:
  SeasonType* season_;
};

}  // namespace hoops

/*

class InterfaceForAdapter{
  virtual void AddAttribute(const std::string& attribute,
                            std::string value) = 0;
}

class AttributeInterface {
  // will only have the shared functions.
}

class AttributeAdapterImpl<T> impl AttributeInterface{
  set_prop1() {
    property_ = 0;
  } .. etc.


  private:
  std::list<T>* property_;
}

class GameHighsAdapter : AttributeAdapterImpl<PlayerMeta::GameHigh> {

}

So how would instances of adapters use this interface impl?
e.g. advanced_adapter = AttributeAdapterImpl<AdvancedSeason>().withAdaptation(
  [](std::string attribute, std::string value){
    // lots of if-else clauses checking each attribute.
});
but if we wanted to share the same type of attribute (regular vs playoff etc),
it would be redundant to to always pass the adaptation method.
so let's make it a class that can be directly implemented.
so...

class AdvancedAdapter extends AttributeAdapterImpl<AdvancedSeason>, AdaptationOnly{
  override: AddAttribute(std::string k, std::string v) {
    // lots of if-else clauses checking each attribute.
  }
}

and now we can do this...
inside of stats_adapters container file:
reg_advanced_adapter = AdvancedAdapter();
playoffs_advanced_adapter = AdvancedAdapter();
all_star_advanced_adapter = AdvancedAdapter();

However, problem is that AdaptionOnly methods need to be grouped with other interface
methods, because inside stats_adapters we have them inside a list of Adapters.
For now we'll leave those methods grouped, and have instances override the AddAttribute method.

BIG question: how do we set the season and how will it be used
with multiple instance of same class season type.
reg_advanced_adapter->SetSeason();
SetSeason():
season = player()-><specific_season_member>;

*/

#endif  // ATTRIBUTE_ADAPTER_IMPL_H_