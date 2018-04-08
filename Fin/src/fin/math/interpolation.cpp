#include "stdafx.h"

#include "common.h"

#include "interpolation.h"

namespace fin::math {
  template<typename T>
  T lerp(const T from, const T to, const double fraction) {
    return from + contain(0, fraction, 1) * (to - from);
  }
}