#pragma once
#include <cstdint>
#include "fin/math/geometry/point3d.h"

namespace fin::graphics {
  enum PrimitiveType {
    PRIMITIVE_POINTS,
    PRIMITIVE_LINES, PRIMITIVE_LINE_LOOP,
    PRIMITIVE_TRIANGLES, PRIMITIVE_TRIANGLE_FAN, PRIMITIVE_TRIANGLE_STRIP,
    PRIMITIVE_QUADS
  };

  enum FaceType {
    FACE_FILLED,
    FACE_WIREFRAME
  };

  class IPrimitives {
    public:
    virtual void begin( PrimitiveType type ) = 0;

    virtual void color3b( uint8_t r, uint8_t g, uint8_t b ) = 0;
    virtual void color3d( double r, double g, double b ) = 0;
    virtual void color4b( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) = 0;
    virtual void color4d( double r, double g, double b, double a ) = 0;

    virtual void uv2d( double u, double v ) = 0;
    virtual void vertex2d( double x, double y ) = 0;
    virtual void vertex3d( double x, double y, double z ) = 0;
    void vertex3d( const math::Point3d& pt ) { vertex3d( pt.x(), pt.y(), pt.z() ); }

    virtual void set_point_radius( double radius ) = 0;
    virtual void set_line_width( double width ) = 0;

    virtual void end() = 0;
  };
}
