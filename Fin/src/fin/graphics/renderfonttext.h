#pragma once

#include <algorithm>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "fin/debug/exception.h"
#include "fin/graphics/irendertext.h"
#include "texture/imagetexture.h"
#include "render2d.h"

namespace fin::graphics {
  typedef struct CharacterInfo {
    double advanceX, advanceY;
    double bitmapWidth, bitmapHeight;
    double bitmapLeft, bitmapTop;
    double textureXOffset;
  } CharacterInfo;

  class RenderFontText : public IRenderText {
    public:
    RenderFontText(Render2d* r2d, IPrimitives* p, ITextures* ts) : r2d(r2d),
                                                                    p(p),
                                                                    ts(ts) {}

    void draw_char(char c, double x, double y, double w, double h)
    override final {
      if (!isDrawingString) {
        ts->bind(texture);
        p->begin(PRIMITIVE_QUADS);
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
        ts->bind(nullptr);
      }
    }

    void draw_string(const std::string& str, double x, double y) override
    final {
      isDrawingString = true;
      ts->bind(texture);
      p->begin(PRIMITIVE_QUADS);
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
      double ss = 100;
      r2d->draw_rectangle(0, 240 - ss, ss, ss, true);
      ts->bind(nullptr);
      isDrawingString = false;
    }

    void init() override final { initialize_texture(ts); }

    private:
    void initialize_texture(ITextures* textures) {
      // TODO: Prevent from reloading freetype, share a common static instance.
      FT_Library ft;
      if (FT_Init_FreeType(&ft)) {
        throw debug::Exception("RenderFreetypeText", "RenderFreetypeText",
                               "Failed to initialize freetype.");
      }
      FT_Face face;
      std::string path = "resources/fonts/tahoma.ttf";
      if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        throw debug::Exception("RenderFreetypeText", "RenderFreetypeText",
                               "Failed to load font: \"" + path + "\"");
      }
      FT_Set_Pixel_Sizes(face, 0, fontSize);
      FT_GlyphSlot g = face->glyph;
      int w = 0, h = 0;
      for (auto i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
          throw debug::Exception("RenderFreetypeText", "RenderFreetypeText",
                                 algorithm::
                                 string_format("Failed to load character: \'%c\'.",
                                               i));
        }
        w += g->bitmap.width;
        h = std::max(h, (int)g->bitmap.rows);
      }
      atlas_width = w = pow(2, ceil(log(w) / log(2)));
      atlas_height = h = pow(2, ceil(log(h) / log(2)));
      int x = 0;
      // TODO: Use 1 channel.
      int depth = 4;
      cimg_library::CImg<unsigned char> img(w, h, 1, depth);
      for (auto r = 0; r < h; r++) {
        for (auto c = 0; c < w; c++) {
          for (int d = 0; d < depth; d++) { img.atXYZC(c, r, 0, d) = 0; }
        }
      }
      for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
          throw debug::Exception("RenderFreetypeText", "RenderFreetypeText",
                                 algorithm::
                                 string_format("Failed to load character: \'%c\'.",
                                               i));
        }
        CharacterInfo ci;
        ci.advanceX = g->advance.x >> 6;
        ci.advanceY = g->advance.y >> 6;
        ci.bitmapWidth = g->bitmap.width;
        ci.bitmapHeight = g->bitmap.rows;
        ci.bitmapLeft = g->bitmap_left;
        ci.bitmapTop = g->bitmap_top;
        ci.textureXOffset = (1. * x) / w;
        map[i] = ci;
        unsigned char* buffer = g->bitmap.buffer;
        for (auto r = 0; r < ci.bitmapHeight; r++) {
          for (auto c = 0; c < ci.bitmapWidth; c++) {
            const int ii = r * ci.bitmapWidth + c;
            unsigned char v = buffer[ii];
            for (int d = 0; d < depth; d++) { img.atXYZC(x + c, r, 0, d) = v; }
          }
        }
        x += g->bitmap.width;
      }
      texture = textures->create_texture_from_image(img.normalize(0, 255));
    }

    int fontSize = 32;
    int atlas_width, atlas_height;
    bool isDrawingString = false;
    Render2d *r2d;
    IPrimitives* p;
    ITextures* ts;
    ImageTexture* texture;
    std::map<char, CharacterInfo> map;
  };
}
