#pragma once

#include "itexture.h"

/**
 * A texture that is loaded from an external file.
 */
namespace fin::graphics {
  class ImageTexture : public ITexture {
    public:
    ImageTexture(const unsigned int id, const int width, const int height) :
      ITexture(id, width, height) {}
  };

}
