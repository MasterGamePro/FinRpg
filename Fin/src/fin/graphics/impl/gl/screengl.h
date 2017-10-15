#pragma once

#include <GL/glew.h>
#include "fin/graphics/iscreen.h"

namespace fin::graphics {
  class ScreenGl : public IScreen {
    public:
    void clear() override final {
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    protected:
    void update_viewport( math::TreeRectangle* rectangle ) override final {
      glViewport( rectangle->get_absolute_x(), rectangle->get_absolute_y(), rectangle->get_clipped_width(), rectangle->get_clipped_height() );
    }
  };
}
