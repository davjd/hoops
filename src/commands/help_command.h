#ifndef HELP_COMMAND_H_
#define HELP_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HelpCommand : public Command {
 public:
  virtual ~HelpCommand() override;
  HelpCommand();
  virtual bool IsValidCommand(const std::string &command) override;
  virtual bool Process(std::vector<std::string> arguments) override;
  virtual bool Process() override;
};

}  // namespace hoops

#endif  // HELP_COMMAND_H_