#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

namespace hoops {
class Command {
 public:
  virtual ~Command() {}
  Command(const std::string& ussage_message);
  std::string usage_message() const;
  virtual bool IsValidCommand(const std::string& command) = 0;
  virtual bool Process(std::vector<std::string> arguments) = 0;
  virtual bool Process() = 0;

 private:
  const std::string usage_message_;
};

}  // namespace hoops

#endif  // COMMAND_H_