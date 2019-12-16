#include "command.h"

#include <iostream>

namespace hoops {
Command::Command(const std::string& usage_message)
    : usage_message_(usage_message) {}
std::string Command::usage_message() const { return usage_message_; }

}  // namespace hoops