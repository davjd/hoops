#ifndef PROFILE_LOADER_H_
#define PROFILE_LOADER_H_

#include "page_reader.h"
#include "player_metadata.h"
#include "loader.h"
#include <string>


namespace hoops{

class HoopsEnvironment {
 public:
  ~HoopsEnvironment() {}
  explicit HoopsEnvironment(PageReader* scraper);

  bool Init();

  // Load/store all files that contain list of players for corresponding letter.
  bool LoadPlayerIndices(bool delay);

  // For every letter, store profile files of all players. We will not have
  // in-memory copies, since it would be too many pages stored. We will however
  // instead create PlayerMetadata objects. If we need to read from the file
  // directly, we can access the url link from the player object.
  bool LoadPlayerProfiles(bool delay);

  // Get the profile page for this page. This page will contain metadata about
  // the given player.
  std::string GetPage(PlayerMetadata& player);

  // Retrieve the PlayerMetadata object that is found in the map given a name.
  PlayerMetadata GetPlayer(const std::string& full_name);

  // ill metadata for given player. Should be moved to more appropriate class.
  void FillPlayerMetadata(PlayerMetadata& player);

  // Delete files that have index of players for all letters.
  bool RemoveIndexFiles();

  ContentPage* CurrentPage();

  PageReader* scraper();

  Loader* loader();

  // Letters to be appended to url of player reference url.
  static const std::string kAlphabet;

  const std::string Alphabet();

  // Options for the environment.
  // struct Options {
  //   Options();

  //   std::string current_page;
  //   std::string Alphabet() { return ""; }
  // };

 private:
  std::unique_ptr<PageReader> scraper_;
  std::unique_ptr<Loader> loader_;
  std::unordered_map<
      char, std::unique_ptr<std::unordered_map<std::string, PlayerMetadata>>>
      letter_players_map;
  std::unordered_map<std::string, char> player_name_to_letter;
};

} // namespace hoops

#endif  // PROFILE_LOADER_H_