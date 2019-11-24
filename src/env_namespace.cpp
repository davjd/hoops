#include "env_namespace.h"
#include <cctype>
#include <utility>

namespace hoops {
namespace env {

namespace filename {

std::string IndexFileName(const std::string& url) {
  return kIndexDirectory + std::to_string(std::hash<std::string>{}(url)) +
         ".html";
}

std::string ProfileFileName(const std::string& url) {
  return kIndexDirectory + kProfileDirectory + GetPlayerLetter(url) + "/" +
         std::to_string(std::hash<std::string>{}(url)) + ".html";
}

std::string ProfileFileName(const std::string& url, const char& letter) {
  return kIndexDirectory + kProfileDirectory + std::string(1, letter) + "/" +
         std::to_string(std::hash<std::string>{}(url)) + ".html";
}

}  // namespace filename

std::string PlayersIndexUrl(const char& letter) {
  if (!isalpha(letter)) return "";
  return url::kBaseUrl + "/" + url::kPlayersUrlSection + std::string(1, letter) +
         "/";
}

// Returns url of page that contains profile of given player url.
// NOTE: This expects the url to be the tail of the url (after kBaseUrl).
std::string PlayerProfileUrl(const std::string& url) {
  if (url.find(".html") == std::string::npos) return "";
  return url::kBaseUrl + url;
}

// Returns url of page that contains profile of given player.
std::string PlayerProfileUrl(const PlayerMetadata& player) {
  if (player.id_info.url.find(".html") == std::string::npos) return "";
  return url::kBaseUrl + player.id_info.url;
}

std::string GetPlayerLetter(const std::string& url) {
  // Find the "players" section of the url and get the letter for this player.
  const std::string token = "/" + url::kPlayersUrlSection;
  int last_slash = url.find(token);
  if (last_slash == std::string::npos ||
      last_slash + token.size() == url.size() - 1) {
    return "";
  }
  return url.substr(last_slash + token.size(), 1);
}

}  // namespace env

}  // namespace hoops