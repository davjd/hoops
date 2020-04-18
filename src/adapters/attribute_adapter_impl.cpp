#include "attribute_adapter_impl.h"

#include "player_metadata.h"
#include "util.h"

#include <iostream>

namespace hoops {

template <typename T>
AttributeAdapterImpl<T>::AttributeAdapterImpl(PlayerMetadata* mutable_player)
    : AttributeInterface(mutable_player) {}

template <typename T>
AttributeAdapterImpl<T>::AttributeAdapterImpl() = default;

template <typename T>
AttributeAdapterImpl<T>::~AttributeAdapterImpl() {}

template <typename T>
void AttributeAdapterImpl<T>::AddAttribute(const std::string& attribute,
                                           std::string value) {
  // TODO: Empty method doesn't look good here.
}

template <typename T>
void AttributeAdapterImpl<T>::AddSeason() {
  season()->push_back(T());
}

template <typename T>
typename AttributeAdapterImpl<T>::SeasonType*
AttributeAdapterImpl<T>::season() {
  return season_;
}

template <typename T>
void AttributeAdapterImpl<T>::set_season(
    AttributeAdapterImpl<T>::SeasonType* season) {
  season_ = season;
}

template <typename T>
void AttributeAdapterImpl<T>::SetSeason() {
  season_ = nullptr;
}

// Instantiate needed templates.
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::AdvancedStatLine>;
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::GameHighsStatLine>;
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::Per100StatLine>;
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::Per36StatLine>;
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::PerGameStatLine>;
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::PlayStatLine>;
template class AttributeAdapterImpl<
    PlayerMetadata::CareerInformation::ShootingStatLine>;

}  // namespace hoops