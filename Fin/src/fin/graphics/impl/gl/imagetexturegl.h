#pragma once
#include "itexture.h"

namespace fin::graphics {
  class IImageTexture : public ITexture {
    public:
    explicit IImageTexture(const io::File& file) {
      file_ = file;
    }

    int get_width() const override final {}
    int get_height() const override final {}
  };
}
