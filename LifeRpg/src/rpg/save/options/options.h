#pragma once
#include <array>

// TODO: Break off some of these as a WindowOptions class.
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

    private:
    std::array<unsigned int, 2> resolution_;
    bool isFullscreen_;
  };
}
