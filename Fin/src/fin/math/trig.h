#pragma once

namespace fin::math {
  const double kPi = 3.14159265, kTau = 2 * kPi;
  const double kRad2Deg = 180 / kPi, kDeg2Rad = 1 / kRad2Deg;

  double cosr(const double rad);
  double cosd(const double deg);

  double sinr(const double rad);
  double sind(const double deg);

  double tanr(const double rad);
  double tand(const double deg);

  double acosr(const double rad);
  double acosd(const double deg);

  double asinr(const double rad);
  double asind(const double deg);

  double atanr(const double rad);
  double atand(const double deg);

  double fremd(const double deg);

  double angle_distd(const double a, const double b);

  double angle_diffd(const double a, const double b);
}
