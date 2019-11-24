#include "hoops_env.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include "env_namespace.h"
#include "gumbo_scraper.h"
#include "player_extractor.h"
#include "util.h"

namespace hoops {

HoopsEnvironment::HoopsEnvironment(PageReader* scraper)
    : scraper_(std::unique_ptr<PageReader>(scraper)),
      loader_(std::make_unique<Loader>()) {
  for (const char& letter : kAlphabet) {
    letter_players_map.emplace(
        letter,
        std::make_unique<std::unordered_map<std::string, PlayerMetadata>>());
  }
}

bool HoopsEnvironment::Init() {
  if (!LoadPlayerIndices(false)) return false;
  if (!LoadPlayerProfiles(true)) return false;
  return true;
}

// Load/store all files that contain list of players for corresponding letter.
bool HoopsEnvironment::LoadPlayerIndices(bool delay) {
  for (const char& letter : kAlphabet) {
    const std::string url = env::PlayersIndexUrl(letter);
    if (loader_->LoadIndexPage(url)) {
      if (delay) std::this_thread::sleep_for(std::chrono::seconds(3));
      std::cout << env::filename::IndexFileName(url)
                << " was loaded succesfully.\n";
    } else {
      std::cout << env::filename::IndexFileName(url)
                << " was not loaded succesfully.\n";
    }
  }
  return true;
}

// For every letter, store profile files of all players. We will not have
// in-memory copies, since it would be too many pages stored. We will however
// instead create PlayerMetadata objects. If we need to read from the file
// directly, we can access the url link from the player object.
bool HoopsEnvironment::LoadPlayerProfiles(bool delay) {
  for (const char& letter : Alphabet()) {
    std::string player_urls_page =
        loader_->GetContent(env::PlayersIndexUrl(letter));
    if (player_urls_page.empty()) return false;
    // TODO: BBallReferencePage page(player_urls_page,
    // BallReferencePage::PageType::kProfilePage); problem wit this is its
    // making direct reference to BBallRefPage. we could move this function
    // elsewhere, or somehow use ContentPage instead.
    std::cout << "Index page url: " << env::PlayersIndexUrl(letter) << " : "
              << env::filename::IndexFileName(env::PlayersIndexUrl(letter))
              << "\n\n";
    scraper_->SetPageContent(player_urls_page, env::PlayersIndexUrl(letter));

    auto player_map = letter_players_map[letter].get();
    auto scraper_wrapper = dynamic_cast<PlayerExtractor*>(scraper_.get());
    if (!scraper_wrapper) return false;
    for (auto& player : scraper_wrapper->GetPlayers()) {
      // Grab specific url for this player's profile page.
      std::string url = env::PlayerProfileUrl(player.id_info.url);
      if (url.empty()) return false;

      // Delay by a couple of seconds if we need to make a request.
      int delay_s = 0;
      if (!Loader::DoesProfileUrlExist(url)) {
        std::cout << "file doesn't exist.. creating timer..\n";
        std::mt19937 rng(0);
        std::uniform_int_distribution<int> gen(3, 5);
        delay_s = gen(rng);
      }

      std::cout << "grabbing profile page for " << player.GetFullName() << "\n";
      player_map->emplace(string_to_lower(player.GetFullName()), player);
      // TODO: player_name_to_letter->emplace(player.) could instead linearly
      // look for it.
      if (loader_->LoadProfilePage(url)) {
        std::cout << env::filename::ProfileFileName(url)
                  << " was loaded succesfully.\n";
        if (delay_s) std::this_thread::sleep_for(std::chrono::seconds(delay_s));
      } else {
        std::cout << env::filename::ProfileFileName(url)
                  << " was not loaded succesfully.\n";
      }
    }
  }
  return true;
}

// Get the profile page for this page. This page will contain metadata about
// the given player.
std::string HoopsEnvironment::GetPage(const PlayerMetadata& player) {
  const std::string url = env::PlayerProfileUrl(player);
  if (!Loader::DoesProfileUrlExist(url)) {
    return "";
  }
  const std::string file_name = env::filename::ProfileFileName(url);
  return Loader::GetPage(file_name);
}

// Retrieve the PlayerMetadata object that is found in the map given a name.
PlayerMetadata HoopsEnvironment::GetPlayer(const std::string& full_name) {
  // We'll first take a guess at what letter this player belongs to, then
  // linearly look for it if not found. We'll guess that the first letter of
  // the last name is the letter for this player.
  auto space_pos = full_name.find(" ");
  if (space_pos == std::string::npos || space_pos == full_name.size() - 1)
    return PlayerMetadata();
  if (kAlphabet.find(std::tolower(full_name[++space_pos])) == std::string::npos)
    return PlayerMetadata();

  const std::string lowercase_name = string_to_lower(full_name);
  auto letter_map_it = letter_players_map.find(lowercase_name[space_pos]);
  auto player_iter = letter_map_it->second->find(lowercase_name);
  if (player_iter == letter_map_it->second->end()) {
    for (auto& pr : letter_players_map) {
      auto player_iter_guess = pr.second->find(lowercase_name);
      if (player_iter_guess != pr.second->end()) {
        // We've found the letter for this player doing linear search,
        // so return the player object.
        return player_iter_guess->second;
      }
    }
    return PlayerMetadata();
  }
  return player_iter->second;
}

// ill metadata for given player. Should be moved to more appropriate class.
void HoopsEnvironment::FillPlayerMetadata(PlayerMetadata& player) {
  std::cout << "Fill in data for " << player.GetFullName() << "\n";
  const std::string page_content = GetPage(player);
  scraper_->SetPageContent(page_content);

  auto g_scraper = static_cast<GumboScraper*>(scraper_.get());
  CSelection sel = g_scraper->scraper()->find("div#info");
  if (sel.nodeNum() == 0) {
    std::cout << "isempty()\n";
    return;
  } else {
    std::cout << "there exists " << sel.nodeNum()
              << " findings with such query..\n";
  }

  CNode table = sel.nodeAt(0);
  std::cout << table.text() << "\n";
}

// Delete files that have index of players for all letters.
bool HoopsEnvironment::RemoveIndexFiles() {
  for (const char& letter : kAlphabet) {
    std::string file_name = env::PlayersIndexUrl(letter);
    if (Loader::DoesIndexFileExist(file_name)) {
      if (loader_->RemoveFile(env::filename::IndexFileName(file_name)))
        std::cout << "delete successful.\n";
    }
  }
  return true;
}

ContentPage* HoopsEnvironment::CurrentPage() {
  if (!scraper_) return nullptr;
  return scraper()->CurrentPage();
}

PageReader* HoopsEnvironment::scraper() { return scraper_.get(); }

Loader* HoopsEnvironment::loader() { return loader_.get(); }

const std::string HoopsEnvironment::Alphabet() {
  return kAlphabet.substr(0, 1);
}

// For some reason the html table body is commented out before being rendered.
// Therefore, we must remove the comment symbol.
void HoopsEnvironment::FixPage(const PlayerMetadata& player) {
  FixPage(env::filename::ProfileFileName(player.GetFullUrl()));
}

void HoopsEnvironment::FixPage(const std::string& file_name) {
  // Testing with Kelenna Azubuike.
  // Fixing page and then scraping it. Shouldn't need to reset the file because
  // checking has been already added. But copy will be inside of tmp.txt.
  std::string page = Loader::GetPage(file_name);
  if (page.empty()) {
    std::cout << "empty file.\n";
    return;
  }
  // Skip first table body.
  size_t begin_pos = page.find("table_outer_container");
  begin_pos = page.find("table_outer_container", begin_pos + 1);
  size_t end_pos;
  int count = 0;
  while (begin_pos != std::string::npos) {
    if (page.substr(begin_pos - 20, 4) != "<!--") {
      std::cout << "Commented out already...closing.\n";
      break;
    }
    end_pos = page.find("-->", begin_pos);
    if (end_pos == std::string::npos) {
      std::cout << "Couldn't find end.\n";
      break;
    }
    // std::cout << "\n-------begin--------\n" << page.substr(begin_pos - 20,
    // 4); std::cout << "\n-------end--------\n" << page.substr(end_pos, 3);
    page.erase(begin_pos - 20, 4);
    // The positions needs to be modified, since we deleted 4 characters.
    page.erase(end_pos - 4, 3);
    begin_pos = page.find("table_outer_container", begin_pos);
    count += 1;
  }
  std::fstream file(file_name, std::fstream::out | std::fstream::trunc);
  file << page;
  std::cout << "count: " << count << "\n";
}

// table_outer_container: where the contain exists. move up one line and delete
// the line. the first div that contains this isn't actually commented out, so
// need to skip the first one.
// <!-- fs_btf_2 -->

bool HoopsEnvironment::RenameFile(const std::string& file_name) {
  size_t period_pos = file_name.find_last_of('.');
  if (period_pos == std::string::npos) {
    return false;
  }
  std::string new_file_name = file_name.substr(0, ++period_pos) + "html";
  return rename(file_name.c_str(), new_file_name.c_str()) == 0;
}

std::string HoopsEnvironment::OldFileName(const std::string& file_name) {
  size_t period_pos = file_name.find_last_of('.');
  if (period_pos == std::string::npos) {
    return "";
  }
  return file_name.substr(0, ++period_pos) + "txt";
}

bool HoopsEnvironment::IsUsingOldName(const std::string& file_name) {
  return file_name.find(".txt") != std::string::npos;
}

const std::string HoopsEnvironment::kAlphabet = "abcdefghijklmnopqrstuvwxyz";

}  // namespace hoops