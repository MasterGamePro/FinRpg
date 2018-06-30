#pragma once

#include <string>
#include "fin/image/imagedefs.h"

namespace fin {
  namespace graphics {
    class IGraphics;
    class View;
  }

  namespace app {
    class IApp;
    class View;

    class IWindow {
      public:
      virtual ~IWindow() {}

      virtual void set_title(std::string title) = 0;
      virtual void set_size(int width, int height) = 0;
      virtual void set_position(int x, int y) = 0;

      virtual void show() = 0;
      virtual void hide() = 0;

      virtual bool is_closed() = 0;
      virtual void close() = 0;

      virtual bool is_fullscreen() = 0;
      void toggle_fullscreen() { toggle_fullscreen(!is_fullscreen()); }
      virtual void toggle_fullscreen(const bool isFullscreen) = 0;

      virtual void set_size_and_fullscreen(const int width, const int height,
                                           const bool isFullscreen) = 0;

      virtual graphics::View* get_view() = 0;

      virtual void render(graphics::IGraphics* g, IApp* app);

      virtual void save_screenshot(std::string name,
                                   image::ImageFileType imageType) = 0;
    };
  }
}
