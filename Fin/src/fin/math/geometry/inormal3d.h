#pragma once

#include <math.h>
#include "fin/math/trig.h"

namespace fin::math {
  class INormal3d {
    public:
    virtual ~INormal3d() {}

    virtual double x() const = 0;
    virtual double y() const = 0;
    virtual double z() const = 0;

    double length() {
      auto x = this->x(), y = this->y(), z = this->z();
      return sqrt(x*x + y * y + z * z);
    }

    double xy_dirr() const { return atan2(y(), x()); }
    double xy_dird() const { return xy_dirr() * Trig::kRad2Deg; }

    void get_data(double dst[]) const {
      dst[0] = x();
      dst[1] = y();
      dst[2] = z();
      dst[3] = 0;
    }
  };
}
