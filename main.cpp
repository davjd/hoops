#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "bball_page.h"
#include "content_page.h"
#include "env_namespace.h"
#include "gumbo_scraper.h"
#include "hoops_env.h"
#include "loader.h"

#include "Document.h"
#include "Node.h"

// usage:

// compare <type of season> <player_name> <player_name> .....
// pull all stats for the given type of season for all given players.
// could use cout color to depict which player is better.

// get <player_name>
// basic command where all stats brought for given player.

// fun_fact <empty>
// lists a random fun fact from a list of fun facts.
// List: youngest/oldest to win a championship, youngest/oldest to win MVP,
// players with more steals than fouls, players with more assists than points,
// graph with most college going pro, GOAT college (most achievements), biggest
// draft steals of all time.

int main() {
  auto env =
      std::make_unique<hoops::HoopsEnvironment>(new hoops::GumboScraper());
  bool init_status = env->Init();
  if (!init_status) {
    std::cout << "Error initializing environment.\n";
    return 0;
  }
  std::cout << "Finished: " << env->Alphabet() << "\n\n";

  auto player = env->GetPlayer("Carmelo Anthony");
  std::cout << "Getting content for " << player.GetFullName() << " with url "
            << player.GetFullUrl() << "\n";
  auto page =
      new hoops::BBallReferencePage(env->GetPage(player), player.GetFullUrl());
  auto g_scraper = static_cast<hoops::GumboScraper*>(env->scraper());
  g_scraper->SetPage(page);
  if (!g_scraper->FillPlayerMetadata(&player)) {
    std::cout << "Error filling metadata.\n";
  }

  if (!g_scraper->FillNumbers(&player)) {
    std::cout << "Error filling metadata.\n";
  }
  std::cout << "file: "
            << hoops::env::filename::ProfileFileName(player.GetFullUrl())
            << "\n";

  env->Run();
  return 0;
}