#pragma once
#include "itexture.h"
#include "imagetexture.h"

namespace fin::app {

  class TextureUtil {

    public:
    graphics::ImageTexture* load(IFile* file);

    private:
    TextureUtil();
  };
}
