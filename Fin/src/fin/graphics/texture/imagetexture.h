#pragma once
#include "itexture.h"

namespace fin::graphics {
  class ImageTexture : public ITexture {
  public:
    ImageTexture(unsigned int id, int width, int height) : ITexture(id, width, height) {}

  private:

  };
}
