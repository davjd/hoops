#include "help_command.h"

#include <iostream>
#include "hoops_env.h"

namespace hoops {

HelpCommand::HelpCommand(HoopsEnvironment* env)
    : Command(
          "Usage:\n"
          "-help\n"
          "   List valid commands.\n"
          "-quit\n"
          "   Quit hoops program.\n"
          "-fun\n"
          "   Return a fun fact.\n"
          "-pull <player full name>\n"
          "   Return stats for given player.\n"
          "-cmp <playerfull name> <player full name>\n"
          "   Compare the two given players.\n",
          env) {}

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