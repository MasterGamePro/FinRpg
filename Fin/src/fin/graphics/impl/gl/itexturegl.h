#pragma once

namespace fin::graphics {
  class ITextureGl {
    public:
    ITextureGl() {}

    virtual int get_id() const = 0;
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual int reload_context() const = 0;
  };
}
