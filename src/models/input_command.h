#ifndef INPUT_COMMAND
#define INPUT_COMMAND

#include <string>
#include <vector>

namespace hoops {

class InputCommand {
 public:
  ~InputCommand() {}
  InputCommand() = delete;
  InputCommand(const std::string& command_line);

  // Returns whether this command has been processed by a command handler.
  bool was_processed();

  // Returns whether this input requested a quit command.
  bool quit_requested();

  // Returns a list copy of the input line.
  std::vector<std::string> Collect();

  // Returns the name of the requested command handler.
  std::string MainCommand();

  // Sets the line of commands as processed.
  void Processed();

  // Request that we quit processing commands.
  void RequestQuit();

  // Return the input line without the main command (leaving the arguments).
  std::vector<std::string> GetArguments();

 private:
  bool quit_requested_;
  bool was_processed_;
  const std::string command_line_;
  const std::string command_handler_;

  // Helper method to get the main command from the command line passed.
  std::string FindMainCommand(const std::string& command_line);
};

}  // namespace hoops

#endif  // INPUT_COMMAND