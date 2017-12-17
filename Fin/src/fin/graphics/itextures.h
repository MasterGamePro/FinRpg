#pragma once

#define cimg_use_bmp
#define cimg_use_jpeg
#define cimg_use_png
#include "lib/cimg/CImg.h"
#include "fin/io/file.h"
#include "texture/imagetexture.h"

namespace fin::graphics {
  class ITextures {
  public:
    ImageTexture * load_texture(const io::File& file) {
      if (!file.exists()) {
        return nullptr;
      }

      cimg_library::CImg<unsigned char> img(file.get_path().c_str());
      return create_texture_from_image(img.normalize(0, 255));
    }

    virtual void bind(ITexture* texture) = 0;

  private:
    virtual ImageTexture* create_texture_from_image(cimg_library::CImg<unsigned char> img) = 0;
  };
}
