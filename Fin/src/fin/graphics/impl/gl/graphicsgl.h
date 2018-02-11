#pragma once

#include "fin/graphics/igraphics.h"
#include "primitivesgl.h"
#include "screengl.h"
#include "transformgl.h"
#include "texturesgl.h"

namespace fin::graphics {
  class GraphicsGl : public IGraphics {
    public:
    GraphicsGl() : IGraphics(new PrimitivesGl(), new TransformGl(), new ScreenGl(), new TexturesGl()) {}

    void init() override final {
      IGraphics::init();
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    void deinit() override final {}
  };
}
