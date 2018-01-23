#pragma once

#include <string>

namespace fin {
  namespace graphics {
    class IGraphics;
    class View;
  }

  namespace app {
    enum ImageType {
      IMAGE_JPG,
      IMAGE_BMP,
      IMAGE_PNG,
    };

    class IApp;
    class View;

    class IWindow {
      public:
      virtual void set_title( std::string title ) = 0;
      virtual void set_size( int width, int height ) = 0;
      virtual void set_position( int x, int y ) = 0;

      virtual void show() = 0;
      virtual void hide() = 0;

      virtual bool is_closed() = 0;
      virtual void close() = 0;

      virtual void toggle_fullscreen() = 0;

      virtual graphics::View* get_view() = 0;

      virtual void render( graphics::IGraphics* g, IApp* app );

      virtual void save_screenshot( std::string name, ImageType imageType ) = 0;
    };
  }
}