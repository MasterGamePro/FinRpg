#pragma once
#include "iunit.h"
#include "fin/math/geometry/point2d.h"

namespace fin::model {
  class Triangle : public IUnit {
    public:
    void render(graphics::IGraphics* g) const {
      const auto p = g->p();
      p->begin(graphics::PrimitiveType::TRIANGLES);

      p->uv2d(vt1_);
      p->normal3d(vn1_);
      p->vertex3d(v1_);

      p->uv2d(vt2_);
      p->normal3d(vn2_);
      p->vertex3d(v2_);

      p->uv2d(vt3_);
      p->normal3d(vn3_);
      p->vertex3d(v3_);

      p->uv2d(vt4_);
      p->normal3d(vn4_);
      p->vertex3d(v4_);

      p->end();
    }

    private:
    math::Point3d v1_, v2_, v3_, v4_;
    math::Normal3d* vn1_, vn2_, vn3_, vn4_;
    math::Point2d vt1_, vt2_, vt3_, vt4_;
  };
}
