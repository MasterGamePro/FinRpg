#pragma once

#include <GL/glew.h>
#include "fin/graphics/iprimitives.h"

namespace fin::graphics {
  class PrimitivesGl : public IPrimitives {
    public:
    void begin(PrimitiveType type) override final {
      auto glType = -1;

      switch (type) {
        case PRIMITIVE_POINTS:	glType = GL_POINTS;		break;

        case PRIMITIVE_LINES:		glType = GL_LINES;		break;
        case PRIMITIVE_LINE_LOOP: glType = GL_LINE_LOOP; break;

        case PRIMITIVE_TRIANGLES: glType = GL_TRIANGLES;	break;
        case PRIMITIVE_TRIANGLE_FAN: glType = GL_TRIANGLE_FAN; break;
        case PRIMITIVE_TRIANGLE_STRIP: glType = GL_TRIANGLE_STRIP; break;

        case PRIMITIVE_QUADS:		glType = GL_QUADS;		break;
      }

      if (glType != -1) {
        glBegin(glType);
      }
    }

    void color3b(const uint8_t r, const uint8_t g, const uint8_t b) override final { glColor3ub(r, g, b); }
    void color3d(const double r, const double g, const double b) override final { glColor3d(r, g, b); }
    void color4b(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) override final { glColor4ub(r, g, b, a); }
    void color4d(const double r, const double g, const double b, const double a) override final { glColor4d(r, g, b, a); }

    void uv2d(const double u, const double v) override final { glTexCoord2d(u, v); }

    void vertex2d(const double x, const double y) override final { glVertex2d(x, y); }
    void vertex3d(const double x, const double y, const double z) override final { glVertex3d(x, y, z); }

    void set_point_radius(const double radius) override final {
      glPointSize(static_cast<GLfloat>(radius));
    }
    void set_line_width(const double width) override final {
      glLineWidth(static_cast<GLfloat>(width));
    }

    void end() override final { glEnd(); }
  };
}
