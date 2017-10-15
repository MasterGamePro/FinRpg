#pragma once

#include <math.h> 

namespace fin::math {
  class Trig {
    public:
    static const double PI, TAU;
    static const double RAD_2_DEG, DEG_2_RAD;

    static double cosr( double rad ) { return cos( rad ); }
    static double sinr( double rad ) { return sin( rad ); }
    static double cosd( double deg ) { return cosr( deg * DEG_2_RAD ); }
    static double sind( double deg ) { return sinr( deg * DEG_2_RAD ); }

    static double angle_dist( double a, double b ) {
      double phi = fmod( fabs( b - a ), 360 );
      double distance = phi > 180 ? 360 - phi : phi;
      return distance;
    }

    static double angle_diff( double a, double b ) {
      double phi = fmod( fabs( b - a ), 360 );
      double distance = phi > 180 ? 360 - phi : phi;
      int sign = ( a - b >= 0 && a - b <= 180 ) || ( a - b <= -180 && a - b >= -360 ) ? 1 : -1;
      return sign * distance;
    }
  };
}