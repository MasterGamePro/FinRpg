#pragma once

#include <GL/glew.h>
#include "fin/graphics/iprimitives.h"

namespace fin::graphics {
  class PrimitivesGl : public IPrimitives {
    public:
    void begin( PrimitiveType type ) override final {
      int glType = -1;

      switch ( type ) {
        case PRIMITIVE_POINTS:	glType = GL_POINTS;		break;

        case PRIMITIVE_LINES:		glType = GL_LINES;		break;

        case PRIMITIVE_TRIANGLES: glType = GL_TRIANGLES;	break;
        case PRIMITIVE_TRIANGLE_FAN: glType = GL_TRIANGLE_FAN; break;
        case PRIMITIVE_TRIANGLE_STRIP: glType = GL_TRIANGLE_STRIP; break;

        case PRIMITIVE_QUADS:		glType = GL_QUADS;		break;
      }

      if ( glType != -1 ) {
        glBegin( glType );
      }
    }

    void color3b( uint8_t r, uint8_t g, uint8_t b ) override final { glColor3ub( r, g, b ); }
    void color3d( double r, double g, double b ) override final { glColor3d( r, g, b ); }
    void color4b( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) override final { glColor4ub( r, g, b, a ); }
    void color4d( double r, double g, double b, double a ) override final { glColor4d( r, g, b, a ); }

    void uv2d( double u, double v ) override final { glTexCoord2d( u, v ); }

    void vertex2d( double x, double y ) override final { glVertex2d( x, y ); }
    void vertex3d( double x, double y, double z ) override final { glVertex3d( x, y, z ); }

    void set_point_radius( double radius ) override final { glPointSize( radius ); }
    void set_line_width( double width ) override final { glLineWidth( width ); }

    void end() override final { glEnd(); }
  };
}
