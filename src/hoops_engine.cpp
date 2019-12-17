#include "hoops_engine.h"

#include "commands/compare_command.h"
#include "commands/fun_command.h"
#include "commands/help_command.h"
#include "commands/pull_command.h"
#include "commands/quit_command.h"
#include "gumbo_scraper.h"
#include "hoops_env.h"
#include "util.h"

#include <fstream>
#include <iostream>

namespace hoops {

// Create the environment, initialize the array of commands, while passing the
// environment. NOTE: Help command should always be first in the array.
HoopsEngine::HoopsEngine()
    : env_(
          std::make_unique<hoops::HoopsEnvironment>(new hoops::GumboScraper())),
      kCommands{{std::make_unique<HelpCommand>(env_.get()),
                 std::make_unique<PullCommand>(env_.get()),
                 std::make_unique<QuitCommand>(env_.get()),
                 std::make_unique<FunCommand>(env_.get()),
                 std::make_unique<CompareCommand>(env_.get())}} {}

bool HoopsEngine::Start() {
  // Load environment with all players.
  return env_->Init();
}

bool HoopsEngine::Process(const std::string& line) {
  std::vector<std::string> command_vector = split(line, " ");
  bool found = false;
  for (auto& command : kCommands) {
    // Find the correct handler for this command.
    if (command->IsValidCommand(command_vector.at(0))) {
      found = true;
      if (!command->Process(command_vector)) {
        // The handler will tell us whether there was a failure or whether we
        // need to quit by returning false.
        return false;
      }
    }
  }
  if (!found) {
    std::cout << kCommands.at(0)->usage_message();
  }
  return true;
}

void HoopsEngine::Run() {
  std::string line;
  while (std::getline(std::cin, line)) {
    if (!Process(line)) {
      break;
    }
  }
}
}  // namespace hoops