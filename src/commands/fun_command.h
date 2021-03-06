#ifndef FUN_COMMAND_H_
#define FUN_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;

class FunCommand : public Command {
 public:
  virtual ~FunCommand() override;
  FunCommand(HoopsEnvironment* env);
  virtual bool IsValidCommand(const std::string& command) override;

 protected:
  virtual void Process(std::vector<std::string> arguments) override;
  virtual void Process() override;
};

}  // namespace hoops

#endif  // FUN_COMMAND_H_