#ifndef STATS_ADAPTERS_H_
#define STATS_ADAPTERS_H_

#include <array>
#include <memory>

class CNode;

namespace hoops {

class PlayerMetadata;
class AttributeInterface;

class StatsAdapters {
 public:
  ~StatsAdapters();
  StatsAdapters();
  AttributeInterface* GetAdapter(const std::string& adapter_name);
  void SetPlayer(PlayerMetadata* mutable_player);

  static const std::array<
      std::pair<std::string, std::unique_ptr<AttributeInterface> >, 17>
      kAttributeAdapters;
};
}  // namespace hoops
#endif  // STATS_ADAPTERS_H_