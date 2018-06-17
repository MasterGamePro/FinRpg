#pragma once

#define cimg_use_bmp
#define cimg_use_jpeg
#define cimg_use_png
#include <CImg.h>

#include <freetype/freetype.h>
#include <GL/glew.h>

#include "fin/debug/exception.h"
#include "fin/io/file.h"
#include "imagetextureutil.h"

namespace fin::graphics {
  FT_Library* freeTypeLibrary = nullptr;

  void load_font_into_id(std::string fontName, const int fontSize, int id) {
    // TODO: Prevent from reloading freetype, share a common static instance.
    if (freeTypeLibrary != nullptr || FT_Init_FreeType(freeTypeLibrary)) {
      throw debug::Exception("RenderFreetypeText", "RenderFreetypeText",
                             "Failed to initialize freetype.");
    }
    FT_Face face;
    std::string path = algorithm::string_format("resources/fonts/%s.ttf",
                                                fontName);
    if (FT_New_Face(*freeTypeLibrary, path.c_str(), 0, &face)) {
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

    copy_image_into_id(img, id, false);
  }
}
