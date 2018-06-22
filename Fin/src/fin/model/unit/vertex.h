#pragma once
#include "iunit.h"

namespace fin::model {
  class Vertex : public IUnit {
    public:
    void render(graphics::IGraphics* g) const {
      const auto p = g->p();
      p->begin(graphics::PrimitiveType::POINTS);
      p->vertex3d(x_, y_, z_);
      p->end();
    }

    float x() const { return x_; }
    float y() const { return y_; }
    float z() const { return z_; }

    private:
    double x_, y_, z_;
  };
}
