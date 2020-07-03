#include "input_command.h"
#include <iostream>
#include "util.h"

namespace hoops {

InputCommand::InputCommand(const std::string& command_line)
    : command_line_(command_line),
      was_processed_(false),
      quit_requested_(false),
      command_handler_(FindMainCommand(command_line_)),
      found_no_args_(HasNoArguments(command_line)) {}

bool InputCommand::was_processed() { return was_processed_; }

bool InputCommand::quit_requested() { return quit_requested_; }

std::vector<std::string> InputCommand::Collect() {
  return split(command_line_);
}

std::string InputCommand::MainCommand() { return command_handler_; }

void InputCommand::Processed() { was_processed_ = true; }

void InputCommand::RequestQuit() { quit_requested_ = true; }

bool InputCommand::NoArguments() { return found_no_args_; }

std::vector<std::string> InputCommand::GetArguments() {
  auto command_list = Collect();
  // We return an empty list if there are no arguments,
  // else we remove the the command name and return the rest of the input line.
  if (!command_list.empty()) command_list.erase(command_list.begin());
  return command_list;
}

std::string InputCommand::FindMainCommand(const std::string& command_line) {
  auto pos = command_line.find(" ");
  if (pos != std::string::npos) {
    return command_line.substr(0, pos);
  }
  return command_line;
}

bool InputCommand::HasNoArguments(const std::string& command_line) {
  auto pos = command_line.find(" ");
  return pos == std::string::npos || pos == command_line.size() - 1;
}

}  // namespace hoops