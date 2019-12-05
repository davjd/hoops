#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

namespace hoops {
class PlayerMetadata;

// Helper class to do calculations on player statistics.
class Accumulator {
 public:
  Accumulator();
  ~Accumulator();
  float GetAverage(const PlayerMetadata& player);
};

}  // namespace hoops

#endif  // ACCUMULATOR_H_