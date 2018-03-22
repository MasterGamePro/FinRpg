#pragma once
#include <cstdlib>

namespace fin::math {
  class Random {
    public:
    static double randomd() { return (1. * rand()) / RAND_MAX; }
    static double randomd(double min, double max) {
      return min + randomd() * (max - min);
    }

    static int randomi(int min, int max) {
      return static_cast<int>(randomd(min, max));
    }

    private:
    Random() {}
  };
}
