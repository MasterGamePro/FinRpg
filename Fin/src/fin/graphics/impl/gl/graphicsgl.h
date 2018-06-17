#pragma once

#include "fin/graphics/igraphics.h"
#include "primitivesgl.h"
#include "screengl.h"
#include "transformgl.h"
#include "texturesgl.h"
#include "renderfonttextgl.h"

namespace fin::graphics {
  class GraphicsGl : public IGraphics {
    public:
    GraphicsGl() : IGraphics(new PrimitivesGl(), new TransformGl(),
                             new ScreenGl()) {
      _ts = new TexturesGl();
      _rt = new RenderFontTextGl(r2d(), p(), _ts);
    }

    void deinit() override final {}

    ITextures* ts() const override final { return _ts; }
    IRenderText* rt() const override final { return _rt; }

    void reload_context() {
      debug::Log::println("reload context");
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      _ts->reload_context();
      _rt->reload_context();
    }

    private:
    void on_init() override final {
      _rt->init();
      reload_context();
    }

    TexturesGl* _ts;
    RenderFontTextGl* _rt;
  };
}
