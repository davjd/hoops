#ifndef ENV_NAMESPACE_H_
#define ENV_NAMESPACE_H_

#include "player_metadata.h"

#include <string>

namespace hoops {
namespace env {  // Environment related methods and constants.

namespace filename {
// methods and directory definitions will go here.
std::string IndexFileName(const std::string& url);
std::string ProfileFileName(const std::string& url);
std::string ProfileFileName(const std::string& url, const char& letter);

const std::string kIndexDirectory = "pages/";
const std::string kProfileDirectory = "profile/";

}  // namespace filename

namespace url {
const std::string kPlayersUrlSection = "players/";
const std::string kBaseUrl = "https://www.basketball-reference.com";

}  // namespace url

// Returns url of the page that contains list of players for given letter.
std::string PlayersIndexUrl(const char& letter);

// Returns url of page that contains profile of given player url.
std::string PlayerProfileUrl(const std::string& url);

// Returns url of page that contains profile of given player.
std::string PlayerProfileUrl(PlayerMetadata& player);

// Get the letter that this player's directory contains. Usually would be used
// to find which directory this player belongs to.
std::string GetPlayerLetter(const std::string& url);

}  // namespace env

}  // namespace hoops

#endif  // ENV_NAMESPACE_H_