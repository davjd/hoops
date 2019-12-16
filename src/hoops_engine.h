#ifndef HOOPS_ENGINE_H_
#define HOOPS_ENGINE_H_

#include <memory>
#include <string>
#include <vector>

namespace hoops {
class HoopsEnvironment;

class HoopsEngine {
 public:
  virtual ~HoopsEngine() {}
  HoopsEngine();

  // Initialize the environment and begin processing commands.
  void Start();

 private:
  std::unique_ptr<HoopsEnvironment> env_;
};

}  // namespace hoops

#endif  // HOOPS_ENGINE_H_