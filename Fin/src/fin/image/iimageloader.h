#pragma once
#include "fin/io/file.h"
#include "iimage.h"

namespace fin::image {
  class IImageLoader {
    virtual IImage* load(io::File* file) const = 0;
  };
}
