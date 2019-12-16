#include "help_command.h"

#include <iostream>

namespace hoops {

HelpCommand::HelpCommand()
    : Command(
          "Usage:\n"
          "-quit\n"
          "   Quit hoops program.\n"
          "-fun\n"
          "   Returns a fun fact.\n"
          "-pull <player full name>\n"
          "   Returns stats for given player.\n"
          "-cmp <playerfull name> <player full name>\n"
          "   Compares the two given players.\n") {}

HelpCommand::~HelpCommand() {}

bool HelpCommand::IsValidCommand(const std::string& command) {
  return command == "-help" || command == "-h";
}

// Help command won't take arguments.
bool HelpCommand::Process(std::vector<std::string> arguments) {
  std::cout << usage_message();
  return true;
}

bool HelpCommand::Process() {
  std::cout << usage_message();
  return true;
}

}  // namespace hoops