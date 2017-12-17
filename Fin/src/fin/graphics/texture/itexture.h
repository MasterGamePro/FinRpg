#pragma once
#include "../itextures.h"

namespace fin::graphics {
  class ITexture {
  public:
    ITexture(unsigned int id, int width, int height) {
      this->id = id;
      this->width = width;
      this->height = height;
    }

    unsigned int get_id() { return id; }
    int get_width() { return width; }
    int get_height() { return height; }

  private:
    unsigned int id;
    int width;
    int height;
  };
}
