#ifndef HELP_COMMAND_H_
#define HELP_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;

class HelpCommand : public Command {
 public:
  virtual ~HelpCommand() override;
  HelpCommand(HoopsEnvironment* env);
  virtual bool IsValidCommand(const std::string& command) override;

 protected:
  virtual void Process(std::vector<std::string> arguments) override;
  virtual void Process() override;
};

}  // namespace hoops

#endif  // HELP_COMMAND_H_