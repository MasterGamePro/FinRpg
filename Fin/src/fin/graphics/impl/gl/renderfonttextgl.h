#pragma once

#include <map>

#include "fin/graphics/iprimitives.h"
#include "fin/graphics/render2d.h"
#include "fin/graphics/texture.h"

#include "irendertextgl.h"
#include "texturesgl.h"

namespace fin::graphics {
  typedef struct CharacterInfo {
    double advanceX, advanceY;
    double bitmapWidth, bitmapHeight;
    double bitmapLeft, bitmapTop;
    double textureXOffset;
  } CharacterInfo;

  class RenderFontTextGl : public IRenderText {
    public:
    RenderFontTextGl(Render2d* r2d, IPrimitives* p, TexturesGl* ts) : r2d(r2d),
                                                                      p(p),
                                                                      ts(ts) {}

    void draw_char(char c, double x, double y, double w, double h)
    override final {
      if (!isDrawingString) {
        ts->bind(texture);
        p->begin(PrimitiveType::QUADS);
      }
      const CharacterInfo ci = map[c];
      const auto u0 = ci.textureXOffset, v0 = 0.,
        uw = ci.bitmapWidth / atlas_width, vh = ci.bitmapHeight / atlas_height;
      p->uv2d(u0, v0);
      p->vertex2d(x, y);
      p->uv2d(u0 + uw, v0);
      p->vertex2d(x + w, y);
      p->uv2d(u0 + uw, v0 + vh);
      p->vertex2d(x + w, y + h);
      p->uv2d(u0, v0 + vh);
      p->vertex2d(x, y + h);
      if (!isDrawingString) {
        p->end();
        ts->unbind();
      }
    }

    void draw_string(const std::string& str, double x, double y) override
    final {
      isDrawingString = true;
      ts->bind(texture);
      p->begin(PrimitiveType::QUADS);
      double fontHeight = 12;
      const auto s = fontHeight / atlas_height;
      for (auto i = 0; i < str.length(); i++) {
        const auto c = str[i];
        const auto ci = map[c];
        const auto w = s * ci.bitmapWidth,
          h = s * ci.bitmapHeight;
        if (c == ' ') { x += fontHeight / 2; }
        else if (w == 0 || h == 0) { continue; }
        draw_char(c, x + ci.bitmapLeft * s, y + fontHeight - ci.bitmapTop * s,
                  w, h);
        x += ci.advanceX * s;
      }
      p->end();
      ts->unbind();
      isDrawingString = false;
    }

    void init() override final;

    void reload_context() { reload_font_(); }

    private:
    void reload_font_();

    int fontSize = 32;
    int atlas_width, atlas_height;
    bool isDrawingString = false;
    Render2d* r2d;
    IPrimitives* p;
    TexturesGl* ts;
    Texture texture;
    std::map<char, CharacterInfo> map;
  };
}
