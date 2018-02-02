#pragma once

#define cimg_use_bmp
#define cimg_use_jpeg
#define cimg_use_png
#include "CImg.h"
#include "fin/io/file.h"
#include "texture/imagetexture.h"
#include <map>

namespace fin::graphics {
  class ITextures {
  public:
    ImageTexture * load_texture(const io::File& file) {
      std::map<io::File, ImageTexture *>::iterator it = cached_textures.find(file);
      if (it != cached_textures.end()) {
        return it->second;
      }

      if (!file.exists()) {
        return nullptr;
      }

      cimg_library::CImg<unsigned char> img(file.get_path().c_str());
      ImageTexture* texture = create_texture_from_image(img.normalize(0, 255));
      cached_textures[file] = texture;
      return texture;
    }

    virtual void bind(ITexture* texture) = 0;

  private:
    virtual ImageTexture* create_texture_from_image(cimg_library::CImg<unsigned char> img) = 0;

    std::map<io::File, ImageTexture*> cached_textures;
  };
}
