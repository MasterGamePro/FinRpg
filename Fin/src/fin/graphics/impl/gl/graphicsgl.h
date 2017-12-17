#pragma once

#include "fin/graphics/igraphics.h"
#include "primitivesgl.h"
#include "screengl.h"
#include "transformgl.h"

namespace fin::graphics {
  class GraphicsGl : public IGraphics {
    public:
    GraphicsGl() : IGraphics( new PrimitivesGl(), new TransformGl(), new ScreenGl() ) {}

    void init() override final {
      glEnable( GL_DEPTH_TEST );
      glDepthFunc( GL_LEQUAL );
    }
    void deinit() override final {}
  };
}
