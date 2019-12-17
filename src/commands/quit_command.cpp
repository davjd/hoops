#include "quit_command.h"

#include <iostream>
#include "hoops_env.h"

namespace hoops {

QuitCommand::QuitCommand(HoopsEnvironment* env)
    : Command(
          "Usage:\n"
          "-q\n"
          "   Quit hoops program.\n",
          env) {}

QuitCommand::~QuitCommand() {}

bool QuitCommand::IsValidCommand(const std::string& command) {
  return command == "-quit" || command == "-q";
}

// Help command won't take arguments.
bool QuitCommand::Process(std::vector<std::string> arguments) {
  std::cout << usage_message();
  return false;
}

bool QuitCommand::Process() {
  std::cout << usage_message();
  return false;
}

}  // namespace hoops