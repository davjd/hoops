#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;
class InputCommand;

class Command {
 public:
  virtual ~Command();
  Command(const std::string& ussage_message, HoopsEnvironment* env);
  std::string usage_message() const;
  virtual bool IsValidCommand(const std::string& command) = 0;
  HoopsEnvironment* env();
  InputCommand* current_command();
  void SetCurrentCommand(InputCommand* input_command);

  // Process the current input command line and modify its internal state.
  void DoProcess();

 private:
  const std::string usage_message_;

  // This class won't own the HoopsEnvironment.
  HoopsEnvironment* env_;

  // This class won't own the InputCommand.
  InputCommand* current_command_;

 protected:
  // Method to be overwritten with custom processing logic for specific command
  // handler. Used when expecting arguments.
  virtual void Process(std::vector<std::string> arguments) = 0;

  // Method to be overwritten with custom processing logic for specific command
  // handler. Used when not expecting arguments.
  virtual void Process() = 0;
};

}  // namespace hoops

#endif  // COMMAND_H_