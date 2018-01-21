#pragma once

#include "fin/graphics/igraphics.h"

namespace fin::ui {
  class IUiElement {
    public:
    virtual void control_move(double direction) = 0;
    virtual void control_action() = 0;
    virtual void render( graphics::IGraphics* g ) = 0;
  };
}
