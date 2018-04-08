#include "stdafx.h"

#include <math.h>

#include "trig.h"

namespace fin::math {
  double cosr(const double rad) { return cos(rad); }
  double cosd(const double deg) { return cosr(deg * kDeg2Rad); }

  double sinr(const double rad) { return sin(rad); }
  double sind(const double deg) { return sinr(deg * kDeg2Rad); }

  double tanr(const double rad) { return tan(rad); }
  double tand(const double deg) { return tanr(deg * kDeg2Rad); }

  double acosr(const double rad) { return acos(rad); }
  double acosd(const double deg) { return acosr(deg * kDeg2Rad); }

  double asinr(const double rad) { return asin(rad); }
  double asind(const double deg) { return asinr(deg * kDeg2Rad); }

  double atanr(const double rad) { return atan(rad); }
  double atand(const double deg) { return atanr(deg * kDeg2Rad); }

  double fremd(const double deg) { return deg - 360 * floor(deg / 360); }

  double angle_distd(const double a, const double b) {
    const auto phi = fmod(fabs(b - a), 360);
    const auto distance = phi > 180 ? 360 - phi : phi;
    return distance;
  }

  double angle_diffd(const double a, const double b) {
    const auto
      phi = fmod(fabs(b - a), 360),
      distance = phi > 180 ? 360 - phi : phi;
    const auto
      sign = (a - b >= 0 && a - b <= 180) || (a - b <= -180 && a - b >= -360)
      ? 1
      : -1;
    return sign * distance;
  }
}