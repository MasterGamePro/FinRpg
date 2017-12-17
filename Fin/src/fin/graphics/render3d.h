#pragma once

#include "iprimitives.h"

namespace fin::graphics {
  class Render3d {
  public:
    Render3d(IPrimitives* p) { this->p = p; }

    virtual void draw_floor(double x1, double y1, double x2, double y2, double z) {
      p->begin(PRIMITIVE_QUADS);

      p->vertex3d(x1, y1, z);
      p->vertex3d(x2, y1, z);
      p->vertex3d(x2, y2, z);
      p->vertex3d(x1, y2, z);

      p->end();
    }

    virtual void draw_wall(double x1, double y1, double z1, double x2, double y2, double z2) {
      p->begin(PRIMITIVE_QUADS);

      p->vertex3d(x1, y1, z1);
      p->vertex3d(x2, y2, z1);
      p->vertex3d(x2, y2, z2);
      p->vertex3d(x1, y1, z2);

      p->end();
    }

  private:
    IPrimitives * p;
  };
}