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

// Help command won't take arguments, so output help message.
bool QuitCommand::Process(std::vector<std::string> arguments) {
  std::cout << usage_message();
  return true;
}

bool QuitCommand::Process() { return false; }

}  // namespace hoops