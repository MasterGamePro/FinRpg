#pragma once

#include <math.h> 

namespace fin::math {
  class Trig {
    public:
    static const double kPi, kTau;
    static const double kRad2Deg, kDeg2Rad;

    static double cosr(const double rad) { return cos(rad); }
    static double sinr(const double rad) { return sin(rad); }
    static double cosd(const double deg) { return cosr(deg * kDeg2Rad); }
    static double sind(const double deg) { return sinr(deg * kDeg2Rad); }

    static double fremd(const double deg) {
      return deg - 360 * floor(deg / 360);
    }

    static double angle_distd(const double a, const double b) {
      double phi = fmod(fabs(b - a), 360);
      double distance = phi > 180 ? 360 - phi : phi;
      return distance;
    }

    static double angle_diffd(const double a, const double b) {
      const auto
        phi = fmod(fabs(b - a), 360),
        distance = phi > 180 ? 360 - phi : phi;
      const auto
        sign = (a - b >= 0 && a - b <= 180) || (a - b <= -180 && a - b >= -360)
        ? 1 : -1;
      return sign * distance;
    }
  };
}