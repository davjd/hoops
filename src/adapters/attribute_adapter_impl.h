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

  // Overwritten method to determine which season we'll be modifying.
  void SetSeason() override;

 protected:
  SeasonType* season_;
};

}  // namespace hoops

#endif  // ATTRIBUTE_ADAPTER_IMPL_H_