#ifndef PULL_COMMAND_H_
#define PULL_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;

class PullCommand : public Command {
 public:
  virtual ~PullCommand() override;
  PullCommand(HoopsEnvironment* env);
  virtual bool IsValidCommand(const std::string& command) override;
  virtual bool Process(std::vector<std::string> arguments) override;
  virtual bool Process() override;
};

}  // namespace hoops

#endif  // PULL_COMMAND_H_