#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

namespace hoops {
class PlayerMetadata;

// Helper class to do calculations on player statistics.
// TODO: This should do basic calculations, like returning the best/worst season
// for a given player. Currently this is not possible, because the metadata are
// mostly in struct, should first be migrated to classes.
class Accumulator {
 public:
  Accumulator();
  ~Accumulator();
  float GetAverage(const PlayerMetadata& player);
};

}  // namespace hoops

#endif  // ACCUMULATOR_H_