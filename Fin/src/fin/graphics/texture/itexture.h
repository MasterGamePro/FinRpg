#pragma once
#include <string>

namespace fin::graphics {
  class ITexture {
    public:

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    private:
  };
}
