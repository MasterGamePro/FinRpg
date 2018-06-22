#pragma once
#include "fin/graphics/igraphics.h"

namespace fin::model {
  class IUnit {
    public:
    virtual void render(graphics::IGraphics* g) const = 0;
  };
}
