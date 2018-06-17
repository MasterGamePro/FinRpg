#pragma once

#include <math.h>

#include "fin/math/common.h"

namespace fin::math {
  double calc_pt_dis(double x1, double y1, double x2, double y2) {
    return sqrt(sqr(y2 - y1) + sqr(x2 - x1));
  }

  double calc_pt_dir_r(double x1, double y1, double x2, double y2) {
    return atan2(y2 - y1, x2 - x1);
  }

  double calc_pt_dir_d(double x1, double y1, double x2, double y2) {
    return calc_pt_dir_r(x1, y1, x2, y2) / 3.14159 * 180;
  }
}
