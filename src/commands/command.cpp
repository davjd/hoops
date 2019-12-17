#include "command.h"

#include <iostream>
#include "hoops_env.h"

namespace hoops {

Command::~Command() {}

Command::Command(const std::string& usage_message, HoopsEnvironment* env)
    : usage_message_(usage_message), env_(env) {}
std::string Command::usage_message() const { return usage_message_; }

}  // namespace hoops