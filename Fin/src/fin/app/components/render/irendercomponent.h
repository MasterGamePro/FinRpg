#pragma once
#include "fin/app/components/icomponent.h"
#include "fin/graphics/igraphics.h"

namespace fin::app {
  class IRenderComponent : IComponent {
    public:
    virtual void tick_render(graphics::IGraphics* g) = 0;
  };
}
