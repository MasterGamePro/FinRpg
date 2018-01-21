#pragma once

#include "iuielement.h"

namespace fin::ui {
  class IToggleButton : public IUiElement {
    public:
    virtual void control_move( double direction ) = 0;
    virtual void control_action() = 0;
    virtual void render( graphics::IGraphics* g ) = 0;
  };
}