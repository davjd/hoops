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

bool HoopsEngine::Process(InputCommand* input_command) {
  // TODO: We should let the command handlers handle the state of input_command instead of this method.
  const std::string main_command = input_command->MainCommand();
  for (auto& command : kCommands) {
    // Find the correct handler for this command.
    if (command->IsValidCommand(main_command)) {
      auto command_list = input_command->GetArguments();
      input_command->Processed();

      // We'll quit processing commands if a command requests it.
      // TODO: This logic is redundunt and probably not needed.
      bool quit_requested = command_list.empty() ? !command->Process() : !command->Process(command_list);
      if (quit_requested) return false;
    }
  }
  // If we couldn't process the command, output the help message.
  if (!input_command->was_processed()) {
    std::cout << "Couldn't process input..\n";
    std::cout << kCommands.at(0)->usage_message();
  }
  return true;
}

void HoopsEngine::Run() {
  std::string line;
  while (std::getline(std::cin, line)) {
    auto input_command = std::make_unique<InputCommand>(line);
    // TODO: We can now do input_command->WasProcessed() inside here to quit.
    if (!Process(input_command.get())) {
      break;
    }
  }
}
}  // namespace hoops