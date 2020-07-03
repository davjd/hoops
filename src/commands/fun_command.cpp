#include "fun_command.h"

#include <iostream>
#include "hoops_env.h"

namespace hoops {

FunCommand::FunCommand(HoopsEnvironment* env)
    : Command(
          "Usage:\n"
          "-fun\n"
          "   Returns a fun fact.\n",
          env) {}

FunCommand::~FunCommand() {}

bool FunCommand::IsValidCommand(const std::string& command) {
  return command == "-fun" || command == "-f";
}

void FunCommand::Process(std::vector<std::string> arguments) {
  std::cout << usage_message();
}

void FunCommand::Process() { std::cout << usage_message(); }

}  // namespace hoops