#ifndef QUIT_COMMAND_H_
#define QUIT_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class QuitCommand : public Command {
 public:
  virtual ~QuitCommand() override;
  QuitCommand();
  virtual bool IsValidCommand(const std::string &command) override;
  virtual bool Process(std::vector<std::string> arguments) override;
  virtual bool Process() override;
};

}  // namespace hoops

#endif  // QUIT_COMMAND_H_