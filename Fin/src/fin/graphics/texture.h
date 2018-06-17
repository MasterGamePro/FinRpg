#pragma once

// TODO: Don't require friendship like this??
#include "fin/graphics/impl/gl/texturesgl.h"

/**
 * Texture class for Fin. Serves as a reference for an internal texture.
 */

namespace fin::graphics {
  class Texture {
    friend TexturesGl;

    public:
    int get_width() const { return width_; }
    int get_height() const { return height_; }

    bool operator==(const Texture& other) const {
      return internal_data_ == other.internal_data_;
    }

    private:

    virtual void set_size(int width, int height) {
      width_ = width;
      height_ = height;
    }

    /**
    * Returns a pointer to the texture's internal data. This is only accessible
    * by internal graphics classes and must be manually cast to the proper type.
    */
    virtual void* get_internal_data() const { return internal_data_; }
    virtual void set_internal_data(void* internal_data) {
      internal_data_ = internal_data;
    }

    int width_, height_;
    void* internal_data_;
  };
}
