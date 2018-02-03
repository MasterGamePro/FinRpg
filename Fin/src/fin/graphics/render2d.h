#pragma once

#include <math.h>
#include "iprimitives.h"
#include "fin/math/trig.h"

namespace fin::graphics {
  class Render2d {
    public:
    Render2d(IPrimitives* p) { this->p = p; }

    void drawPoint(const double x, const double y) { drawPoint(x, y, 1); }
    void drawPoint(const double x, const double y, const double radius) {
      p->set_point_radius(radius);
      p->begin(PRIMITIVE_POINTS);
      p->vertex2d(x, y);
      p->end();
    }

    void drawLine(const double x1, const double y1, const double x2, const double y2) { drawLine(x1, y1, x2, y2, 1); }
    void drawLine(const double x1, const double y1, const double x2, const double y2, const double width) {
      p->set_line_width(width);
      p->begin(PRIMITIVE_LINES);
      p->vertex2d(x1, y1);
      p->vertex2d(x2, y2);
      p->end();
    }

    virtual void drawRectangle(const double x, const double y, const double w, const double h, const bool isFilled) {
      p->begin(isFilled ? PRIMITIVE_QUADS : PRIMITIVE_LINE_LOOP);
      p->uv2d(0, 0);
      p->vertex2d(x, y);
      p->uv2d(1, 0);
      p->vertex2d(x + w, y);
      p->uv2d(1, 1);
      p->vertex2d(x + w, y + h);
      p->uv2d(0, 1);
      p->vertex2d(x, y + h);
      p->end();
    }
    virtual void strokeRectangle(const double x, const double y, const double w, const double h) { drawRectangle(x, y, w, h, false); }
    virtual void fillRectangle(const double x, const double y, const double w, const double h) { drawRectangle(x, y, w, h, true); }

    virtual void drawPolygon(const double x, const double y, const double r, 
                             const int numPts, const bool isFilled) {
      p->begin(isFilled ? PRIMITIVE_TRIANGLE_FAN : PRIMITIVE_LINE_LOOP);
      if (isFilled) {
        p->uv2d(.5, .5);
        p->vertex2d(x, y);
      }
      const int toCount = (isFilled) ? numPts + 1 : numPts;
      for (int i = 0; i < toCount; i++) {
        double dir = ((1.*i) / numPts) * 2 * 3.14159;
        double xF = cos(dir), yF = sin(dir);

        p->uv2d(.5 + .5*xF, .5 + .5*yF);
        p->vertex2d(x + r * xF, y + r * yF);
      }
      p->end();
    }
    virtual void strokePolygon(const double x, const double y, const double r,
                               const int numPts) {
      drawPolygon(x, y, r, numPts, false);
    }
    virtual void fillPolygon(const double x, const double y, const double r,
                             const int numPts) {
      drawPolygon(x, y, r, numPts, true);
    }

    virtual void drawCircle(const double x, const double y, const double r,
                            const bool isFilled) {
      drawPolygon(x, y, r, static_cast<int>(ceil(math::Trig::TAU * r / 5)),
                  isFilled);
    }
    virtual void strokeCircle(const double x, const double y, const double r) {
      drawCircle(x, y, r, false);
    }
    virtual void fillCircle(const double x, const double y, const double r) {
      drawCircle(x, y, r, true);
    }

    private:
    IPrimitives * p;
  };
}
