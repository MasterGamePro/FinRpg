#pragma once

namespace fin::math {
  class Interpolate {
    public:
    static double d( double a, double b, double f ) { return a + f * ( b - a ); }

    private:
    Interpolate() {};
  };
}