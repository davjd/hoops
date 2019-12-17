#ifndef COMPARE_COMMAND_H_
#define COMPARE_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;

class CompareCommand : public Command {
 public:
  virtual ~CompareCommand() override;
  CompareCommand(HoopsEnvironment* env);
  virtual bool IsValidCommand(const std::string& command) override;
  virtual bool Process(std::vector<std::string> arguments) override;
  virtual bool Process() override;
};

}  // namespace hoops

#endif  // COMPARE_COMMAND_H_