#include "compare_command.h"

#include <iostream>
#include "hoops_env.h"

namespace hoops {

CompareCommand::CompareCommand(HoopsEnvironment* env)
    : Command(
          "Usage:\n"
          "-cmp <playerfull name> <player full name>\n"
          "   Compares the two given players.\n",
          env) {}

CompareCommand::~CompareCommand() {}

bool CompareCommand::IsValidCommand(const std::string& command) {
  return command == "-cmp" || command == "-compare" || command == "-c";
}

bool CompareCommand::Process(std::vector<std::string> arguments) {
  std::cout << usage_message();
  return true;
}

bool CompareCommand::Process() {
  std::cout << usage_message();
  return true;
}

}  // namespace hoops