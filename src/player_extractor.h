#ifndef PLAYER_EXTRACTOR_H_
#define PLAYER_EXTRACTOR_H_

#include <string>

#include "player_metadata.h"

namespace hoops {
// Interface to extract player metadata.
// NOTE: The implementation of these methods should scrape actual content.
// Each method might also require different page content (index vs profile
// pages), therefore there must be some mechanism to check that we have the
// correct page before doing the scraping.
class PlayerExtractor {
 public:
  virtual ~PlayerExtractor() {}
  virtual std::string GetPlayerNames() = 0;
  virtual std::vector<PlayerMetadata> GetPlayers() = 0;
  virtual PlayerMetadata GetPlayer(const std::string& name) = 0;

  // Maybe create new interface that deals with profile page content. Though
  // this might be too restrictive (and would reveal implementation detaisl).
  virtual bool FillPlayerMetadata(PlayerMetadata* mutable_player) = 0;
};

}  // namespace hoops

#endif