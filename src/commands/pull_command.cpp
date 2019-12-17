#include "pull_command.h"

#include <iostream>
#include "hoops_env.h"

namespace hoops {

PullCommand::PullCommand(HoopsEnvironment* env)
    : Command(
          "Usage:\n"
          "-pull <player full name>\n"
          "   Returns stats for given player.\n",
          env) {}

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