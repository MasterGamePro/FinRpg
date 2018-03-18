#pragma once
#include <cstdint>
#include "fin/graphics/color.h"

namespace fin::image {
  class IImage {
    public:
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual graphics::Color get_color(const int x, const int y) const = 0;

    virtual void get_data(uint8_t*& ptr, int& length) = 0;
  };
}
