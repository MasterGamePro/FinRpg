#include "stdafx.h"

#include <cstdlib>

#include "random.h"

namespace fin::math {
  double randomd() { return (1. * rand()) / RAND_MAX; }
  double randomd(const double min, const double max) {
    return min + randomd() * (max - min);
  }

  int randomi(const int min, const int max) {
    return static_cast<int>(randomd(min, max));
  }
}