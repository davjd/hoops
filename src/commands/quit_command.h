#ifndef QUIT_COMMAND_H_
#define QUIT_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;

class QuitCommand : public Command {
 public:
  virtual ~QuitCommand() override;
  QuitCommand(HoopsEnvironment* env);
  virtual bool IsValidCommand(const std::string& command) override;

 protected:
  virtual void Process(std::vector<std::string> arguments) override;
  virtual void Process() override;
};

}  // namespace hoops

#endif  // QUIT_COMMAND_H_