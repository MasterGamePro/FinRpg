#pragma once
#include <array>
#include "fin/app/iwindow.h"

namespace rpg::save {
  class Options {
    public:

    unsigned int get_width() const { return resolution_[0]; }
    unsigned int get_height() const { return resolution_[1]; }

    void set_resolution(const unsigned int width,
                        const unsigned int height) {
      resolution_[0] = width;
      resolution_[1] = height;
    }

    bool is_fullscreen() const { return isFullscreen_; }

    void toggle_fullscreen(const bool isFullscreen) {
      isFullscreen_ = isFullscreen;
    }

    void apply(fin::app::IWindow* window) const {
      window->set_size(resolution_[0], resolution_[1]);
      window->toggle_fullscreen(isFullscreen_);
    }

    private:
    std::array<unsigned int, 2> resolution_;
    bool isFullscreen_;
  };
}
