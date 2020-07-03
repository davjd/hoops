#ifndef PULL_COMMAND_H_
#define PULL_COMMAND_H_

#include "command.h"

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;
class PlayerMetadata;

class PullCommand : public Command {
 public:
  virtual ~PullCommand() override;
  PullCommand(HoopsEnvironment* env);
  virtual bool IsValidCommand(const std::string& command) override;

 protected:
  virtual void Process(std::vector<std::string> arguments) override;
  virtual void Process() override;

 private:
  void OutputStatistics(const PlayerMetadata& player);
};

}  // namespace hoops

#endif  // PULL_COMMAND_H_