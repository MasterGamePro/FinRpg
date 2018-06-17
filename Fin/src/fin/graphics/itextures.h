#pragma once

#define cimg_use_bmp
#define cimg_use_jpeg
#define cimg_use_png
#include "CImg.h"

#include "fin/io/file.h"

namespace fin::graphics {
  class Texture;

  class ITextures {
    public:
    ITextures() { }
    virtual ~ITextures() {}

    virtual Texture load_texture(const io::File& file) = 0;
    virtual Texture create_texture_from_image(
      cimg_library::CImg<unsigned char> img) = 0;

    virtual void bind(const Texture& texture) = 0;
    virtual void unbind() = 0;
  };
}
