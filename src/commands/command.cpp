#include "command.h"

#include <iostream>
#include "hoops_env.h"
#include "models/input_command.h"

namespace hoops {

Command::~Command() {}

Command::Command(const std::string& usage_message, HoopsEnvironment* env)
    : usage_message_(usage_message), env_(env) {}

std::string Command::usage_message() const { return usage_message_; }

HoopsEnvironment* Command::env() { return env_; }

InputCommand* Command::current_command() { return current_command_; }

void Command::SetCurrentCommand(InputCommand* input_command) {
  current_command_ = input_command;
}

void Command::DoProcess() {
  if (current_command_ == nullptr) return;
  if (current_command_->NoArguments()) {
    Process();
  } else {
    Process(current_command_->GetArguments());
  }
  // Signal that we've processed the input command line.
  current_command_->Processed();
}

}  // namespace hoops