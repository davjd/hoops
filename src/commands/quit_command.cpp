#include "quit_command.h"

#include <iostream>

namespace hoops {

QuitCommand::QuitCommand()
    : Command(
          "Usage:\n"
          "-q\n"
          "   Quit hoops program.\n") {}

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