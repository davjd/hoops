#include "pull_command.h"

#include <iostream>

namespace hoops {

PullCommand::PullCommand()
    : Command(
          "Usage:\n"
          "-pull <player full name>\n"
          "   Returns stats for given player.\n") {}

PullCommand::~PullCommand() {}

bool PullCommand::IsValidCommand(const std::string& command) {
  return command == "-pull" || command == "-p";
}

// Help command won't take arguments.
bool PullCommand::Process(std::vector<std::string> arguments) {
  std::cout << usage_message();
  return true;
}

bool PullCommand::Process() {
  std::cout << usage_message();
  return true;
}

}  // namespace hoops