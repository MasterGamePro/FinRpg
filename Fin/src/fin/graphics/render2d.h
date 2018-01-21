#pragma once

#include <math.h>
#include "iprimitives.h"
#include "fin/math/trig.h"

namespace fin::graphics {
  class Render2d {
    public:
    Render2d( IPrimitives* p ) { this->p = p; }

    void drawPoint( double x, double y ) { drawPoint( x, y, 1 ); }
    void drawPoint( double x, double y, double radius ) {
      p->set_point_radius( radius );
      p->begin( PRIMITIVE_POINTS );
      p->vertex2d( x, y );
      p->end();
    }

    void drawLine( double x1, double y1, double x2, double y2 ) { drawLine( x1, y1, x2, y2, 1 ); }
    void drawLine( double x1, double y1, double x2, double y2, double width ) {
      p->set_line_width( width );
      p->begin( PRIMITIVE_LINES );
      p->vertex2d( x1, y1 );
      p->vertex2d( x2, y2 );
      p->end();
    }

    virtual void drawRectangle( double x, double y, double w, double h, bool isFilled ) {
      p->begin( isFilled ? PRIMITIVE_QUADS : PRIMITIVE_LINE_LOOP );
      p->uv2d( 0, 0 );
      p->vertex2d( x, y );
      p->uv2d( 1, 0 );
      p->vertex2d( x + w, y );
      p->uv2d( 1, 1 );
      p->vertex2d( x + w, y + h );
      p->uv2d( 0, 1 );
      p->vertex2d( x, y + h );
      p->end();
    }
    virtual void strokeRectangle( double x, double y, double w, double h ) { drawRectangle( x, y, w, h, false ); }
    virtual void fillRectangle( double x, double y, double w, double h ) { drawRectangle( x, y, w, h, true ); }

    virtual void drawPolygon( double x, double y, double r, int numPts, bool isFilled ) {
      p->begin( isFilled ? PRIMITIVE_TRIANGLE_FAN : PRIMITIVE_LINE_LOOP );
      if ( isFilled ) {
        p->uv2d( .5, .5 );
        p->vertex2d( x, y );
      }
      const int toCount = ( isFilled ) ? numPts + 1 : numPts;
      for ( int i = 0; i < toCount; i++ ) {
        double dir = ( ( 1.*i ) / numPts ) * 2 * 3.14159;
        double xF = cos( dir ), yF = sin( dir );

        p->uv2d( .5 + .5*xF, .5 + .5*yF );
        p->vertex2d( x + r*xF, y + r*yF );
      }
      p->end();
    }
    virtual void strokePolygon( double x, double y, double r, int numPts ) { drawPolygon( x, y, r, numPts, false ); }
    virtual void fillPolygon( double x, double y, double r, int numPts ) { drawPolygon( x, y, r, numPts, true ); }

    virtual void drawCircle( double x, double y, double r, bool isFilled ) { drawPolygon( x, y, r, math::Trig::TAU * r / 5, isFilled ); }
    virtual void strokeCircle( double x, double y, double r ) { drawCircle( x, y, r, false ); }
    virtual void fillCircle( double x, double y, double r ) { drawCircle( x, y, r, true ); }

    private:
    IPrimitives* p;
  };
}
