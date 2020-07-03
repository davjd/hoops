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
// environment. NOTE: Help command_handler should always be first in the array.
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

void HoopsEngine::Process(InputCommand* input_command) {
  const std::string main_command = input_command->MainCommand();
  // Find the correct handler for the input_command line.
  auto it = std::find_if(kCommands.begin(), kCommands.end(),
                         [&](auto& command_handler) {
                           return command_handler->IsValidCommand(main_command);
                         });
  (*it)->SetCurrentCommand(input_command);
  (*it)->DoProcess();
}

void HoopsEngine::Run() {
  std::string line;
  while (std::getline(std::cin, line)) {
    auto input_command = std::make_unique<InputCommand>(line);
    Process(input_command.get());
    // If we couldn't process the command, output the help message.
    if (!input_command->was_processed()) {
      std::cout << "Couldn't process input..\n";
      std::cout << kCommands.at(0)->usage_message();
    }
    if (input_command->quit_requested()) break;
  }
}
}  // namespace hoops