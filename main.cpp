#include "hoops_engine.h"

#include <iostream>
#include <memory>

int main() {
  auto engine = std::make_unique<hoops::HoopsEngine>();

  // Initialize the engine.
  if (!engine->Start()) {
    std::cout << "Error starting hoops program.\n";
    return 1;
  }

  // Begin processing command inputs.
  engine->Run();
  return 0;
}