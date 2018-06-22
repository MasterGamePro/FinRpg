#pragma once
#include <vector>
#include "fin/model/unit/iunit.h"

// TODO: "Bake" model into an optimized version.
// TODO: Merge similar/basic units into _List units.
// TODO: Use better array to cut down on copying.

namespace fin::model {
  class SimpleModel {
    public:
    explicit SimpleModel(const std::vector<IUnit*> units) : units_(units) {}

    void render(graphics::IGraphics* g) const {
      for (const auto unit : units_) { unit->render(g); }
    }

    private:
    std::vector<IUnit*> units_;
  };
}
