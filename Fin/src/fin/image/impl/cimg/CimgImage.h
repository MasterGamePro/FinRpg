#pragma once
#include "fin/image/iimage.h"
#include <CImg.h>

namespace fin::image {
  class CimgImage : public IImage {
    public:
    CimgImage(cimg_library::CImg<uint8_t> img) {
      
    }

    int get_width() const override final {
      return img.width();
    }

    int get_height() const override final {
      return img.height();
    }

    graphics::Color get_color(const int x, const int y) const override final {
      return graphics::Color(img(x, y));
    }

    void get_data(uint8_t*& ptr, int& length) override final {
      ptr = img.data();
      length = img.size();
    }

    private:
    cimg_library::CImg<GLubyte> img;  (width, height, 1, channelCount);
  };
}
