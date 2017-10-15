#pragma once

#include "camera.h"

namespace fin {
  namespace graphics {
    class IGraphics;

    class View {
      public:
      View() {
        rectangle = new math::TreeRectangle();
      }

      void set_camera( Camera* camera ) {
        this->camera = camera;
      }

      math::TreeRectangle* get_rectangle() const { return rectangle; }

      void render( IGraphics* g );

      private:
      math::TreeRectangle* rectangle;
      Camera* camera;
    };
  }
}