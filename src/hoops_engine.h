#ifndef HOOPS_ENGINE_H_
#define HOOPS_ENGINE_H_

#include <array>
#include <memory>
#include <string>

#include "commands/command.h"

namespace hoops {
class HoopsEnvironment;

class HoopsEngine {
 public:
  virtual ~HoopsEngine() {}
  HoopsEngine();

  // Initialize the environment and begin processing commands.
  bool Start();

  // Procces the given command input.
  bool Process(const std::string& line);

  // Continously ask for input from the user and process input.
  void Run();

 private:
  std::unique_ptr<HoopsEnvironment> env_;
  const std::array<std::unique_ptr<Command>, 5> kCommands;
};

}  // namespace hoops

#endif  // HOOPS_ENGINE_H_