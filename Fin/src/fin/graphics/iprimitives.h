#pragma once
#include <cstdint>
#include "fin/math/geometry/inormal3d.h"
#include "fin/math/geometry/point2d.h"
#include "fin/math/geometry/point3d.h"
#include "color.h"

namespace fin::graphics {
  enum class PrimitiveType {
    POINTS,
    LINES, LINE_LOOP,
    TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP,
    QUADS
  };

  enum class FaceType {
    FILLED,
    WIREFRAME
  };

  class IPrimitives {
    public:
    virtual void begin(PrimitiveType type) = 0;

    virtual void color(Color color) {
      color4b(color.r_b(), color.g_b(), color.b_b(), color.a_b());
    }
    virtual void color3b(uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void color3d(double r, double g, double b) = 0;
    virtual void color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void color4d(double r, double g, double b, double a) = 0;

    virtual void uv2d(double u, double v) = 0;
    virtual void uv2d(const math::Point2d& uv) { uv2d(uv.x(), uv.y()); }

    virtual void normal3d(const double nx, const double ny, const double nz) = 0;
    virtual void normal3d(const math::INormal3d* nxyz) {
      normal3d(nxyz->x(), nxyz->y(), nxyz->z());
    }

    virtual void vertex2d(double x, double y) = 0;
    virtual void vertex3d(double x, double y, double z) = 0;
    void vertex3d(const math::Point3d& xyz) {
      vertex3d(xyz.x(), xyz.y(), xyz.z());
    }

    virtual void set_point_radius(double radius) = 0;
    virtual void set_line_width(double width) = 0;

    virtual void end() = 0;
  };
}
