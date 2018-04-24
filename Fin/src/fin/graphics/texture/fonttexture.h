#pragma once
#include "itexture.h"

namespace fin::graphics {
  class FontTexture : public ITexture {
    public:
    FontTexture(const std::string fontName, const int size) {
      file_ = file;
      reload();
    }

    int get_width() const override final {}
    int get_height() const override final {}

    private:
    virtual void reload() {
      
    }

    io::File file_;
  };
}
