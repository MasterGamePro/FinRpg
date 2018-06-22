#pragma once
#include "iunit.h"
#include "vertex.h"

namespace fin::model {
  class Line : public IUnit {
    public:
    void render(graphics::IGraphics* g) const {
      const auto p = g->p();
      p->begin(graphics::PrimitiveType::LINES);
      for (const auto v : vertices) { p->vertex3d(v->x(), v->y(), v->z()); }
      p->end();
    }

    const std::vector<Vertex*>& get_vertices() const { return vertices; }

    private:
    std::vector<math::Point3d*> vertices;
  };
}
