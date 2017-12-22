#pragma once
#include "fin/math/trig.h"
#include <algorithm>

namespace fin::graphics {
  class Color {
    public:
    static Color from_rgba( int rgba ) {
      Color c;
      c.rgba = rgba;
      return c;
    }
    static Color from_rgb_d( double r, double g, double b ) { return from_rgba_d( r, g, b, 1 ); }
    static Color from_rgba_d( double r, double g, double b, double a ) { return from_rgba_i( ( int ) ( 255 * r ), ( int ) ( 255 * g ), ( int ) ( 255 * b ), 255 ); }
    static Color from_rgb_i( int r, int g, int b ) { return from_rgba_i( r, g, b, 255 ); }
    static Color from_rgba_i( int r, int g, int b, int a ) { return from_rgba( r & 0xFF << 24 + g & 0xFF << 16 + b & 0xFF << 8 + a & 0xFF ); }

    double r_d() const { return r_i() / 255.; }
    int r_i() const { return rgba >> 24 & 0xff; }
    double g_d() const { return g_i() / 255.; }
    int g_i() const { return rgba >> 16 & 0xff; }
    double b_d() const { return b_i() / 255.; }
    int b_i() const { return rgba >> 8 & 0xff; }
    double a_d() const { return a_i() / 255.; }
    int a_i() const { return rgba & 0xff; }

    double h_r() { return h_d() * math::Trig::DEG_2_RAD; }
    double h_d() {
      double r = r_d(), g = g_d(), b = b_d();
      double ma = std::max( r, std::max( g, b ) ), mi = std::min( r, std::min( g, b ) );
      double d = ma - mi;
      if ( ma == mi ) {
        return 0;
      }
      double h;
      if ( ma == r ) {
        h = ( g - b ) / d + ( g < b ? 6 : 0 );
      }
      else if ( ma == g ) {
        h = ( b - r ) / d + 2;
      }
      else if ( ma == b ) {
        h = ( r - g ) / d + 4;
      }
      return h * 60;
    }
    int s_i() { return s_d() * 255; }
    double s_d() {
      double r = r_d(),
        g = g_d(),
        b = b_d();
      double ma = std::max( r, std::max( g, b ) ),
        mi = std::min( r, std::min( g, b ) );
      return ma == 0 ? 0 : ( ma - mi ) / ma;
    }
    int v_i() const { return ( int ) ( .21*r_i() + .71*g_i() + .08*b_i() ); }
    double v_d() const { return v_i() / 255.; }

    private:
    int rgba;
  };
}
