#pragma once

#include <GL/glew.h>
#include "fin/graphics/iscreen.h"

namespace fin::graphics {
  class ScreenGl : public IScreen {
    public:
    void clear() override final {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void clear_color3d(const double r, const double g, const double b)
      override final {
      glClearColor(static_cast<GLclampf>(r),
                   static_cast<GLclampf>(g),
                   static_cast<GLclampf>(b),
                   1);
    }
    void clear_color4d(const double r, const double g, const double b,
                       const double a) override final {
      glClearColor(static_cast<GLclampf>(r),
                   static_cast<GLclampf>(g),
                   static_cast<GLclampf>(b),
                   static_cast<GLclampf>(a));
    }

    protected:
    void update_viewport(math::TreeRectangle* rectangle) override final {
      glViewport(static_cast<GLint>(rectangle->get_absolute_x()),
                 static_cast<GLint>(rectangle->get_absolute_y()),
                 static_cast<GLsizei>(rectangle->get_clipped_width()),
                 static_cast<GLsizei>(rectangle->get_clipped_height()));
    }
  };
}
