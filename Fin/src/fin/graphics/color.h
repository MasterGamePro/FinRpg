#pragma once
#include <cstdint>
#include "fin/math/trig.h"
#include <algorithm>

namespace fin::graphics {
  class Color {
    public:
    static Color from_rgba( const uint32_t rgba ) {
      Color c;
      c.rgba = rgba;
      return c;
    }
    static Color from_rgb_d( const double r, const double g, const double b ) { return from_rgba_d( r, g, b, 1 ); }
    static Color from_rgba_d( const double r, const double g, const double b, const double a ) { return from_rgba_b( ( uint8_t ) ( 255 * r ), ( uint8_t ) ( 255 * g ), ( uint8_t ) ( 255 * b ), 255 ); }
    static Color from_rgb_b( const uint8_t r, const uint8_t g, const uint8_t b ) { return from_rgba_b( r, g, b, 255 ); }
    static Color from_rgba_b( const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a ) { return from_rgba( r & 0xFF << 24 + g & 0xFF << 16 + b & 0xFF << 8 + a & 0xFF ); }

    double r_d() const { return r_b() / 255.; }
    uint8_t r_b() const { return rgba >> 24 & 0xff; }
    double g_d() const { return g_b() / 255.; }
    uint8_t g_b() const { return rgba >> 16 & 0xff; }
    double b_d() const { return b_b() / 255.; }
    uint8_t b_b() const { return rgba >> 8 & 0xff; }
    double a_d() const { return a_b() / 255.; }
    uint8_t a_b() const { return rgba & 0xff; }

    double h_r() const { return h_d() * math::Trig::DEG_2_RAD; }
    double h_d() const {
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
    uint8_t s_b() const { return s_d() * 255; }
    double s_d() const {
      double r = r_d(),
        g = g_d(),
        b = b_d();
      double ma = std::max( r, std::max( g, b ) ),
        mi = std::min( r, std::min( g, b ) );
      return ma == 0 ? 0 : ( ma - mi ) / ma;
    }
    uint8_t v_b() const { return ( uint8_t ) ( .21*r_b() + .71*g_b() + .08*b_b() ); }
    double v_d() const { return v_b() / 255.; }

    private:
    uint32_t rgba;
  };
}
