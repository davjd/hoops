#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "bball_page.h"
#include "content_page.h"
#include "env_namespace.h"
#include "gumbo_scraper.h"
#include "hoops_engine.h"
#include "hoops_env.h"
#include "loader.h"

#include "Document.h"
#include "Node.h"

// Usage:
// -compare <type of season> <player_name> <player_name> .....
// pull all stats for the given type of season for all given players.
// could use cout color to depict which player is better.

// -pull <player_name>
// basic command where all stats brought for given player.

// -fun <empty>
// Gets a random fun fact from a list of fun facts.
// List: youngest/oldest to win a championship, youngest/oldest to win MVP,
// players with more steals than fouls, players with more assists than points,
// graph with most college going pro, GOAT college (most achievements), biggest
// draft steals of all time.

// Pull is the only command fully implemented.

int main() {
  auto engine = std::make_unique<hoops::HoopsEngine>();

  // Initialize the engine.
  if (!engine->Start()) {
    std::cout << "Error starting hoops program.\n";
    return 1;
  }

  // Begin processing command inputs.
  engine->Run();
  return 0;
}