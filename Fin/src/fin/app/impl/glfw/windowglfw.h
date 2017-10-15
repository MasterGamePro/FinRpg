#pragma once

#include <boost/algorithm/string.hpp>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "fin/app/iwindow.h"
#include "fin/graphics/view.h"
#include "fin/input/impl/glfw/keyboardglfw.h"

#define cimg_use_jpeg
#define cimg_use_png
#define cimg_use_bmp
#include "lib/cimg/CImg.h"

namespace fin::app {
  std::function< void() > tickCallback;

  class WindowGlfw : public IWindow {
    public:
    WindowGlfw() {
      view = new graphics::View();
      create_glfw_window( false );
    }

    void set_title( std::string title ) override final {
      this->title = title;
      glfwSetWindowTitle( window, title.c_str() );
    };
    void set_size( int width, int height ) override final { glfwSetWindowSize( window, this->width = width, this->height = height ); }
    void set_position( int x, int y ) override final { glfwSetWindowPos( window, x, y ); }

    void show() override final { glfwShowWindow( window ); }
    void hide() override final { glfwHideWindow( window ); }
    void close() override final { glfwSetWindowShouldClose( window, true ); }
    void toggle_fullscreen() override final { create_glfw_window( !isFullscreen ); }

    void render( graphics::IGraphics* g, IApp* app ) override final {
      //!glfwWindowShouldClose( window ) );
      glfwMakeContextCurrent( window );

      IWindow::render( g, app );

      glfwSwapBuffers( window );
      //glfwDestroyWindow( window );

      //glfwSetWindowShouldClose( window, true );
    }

    GLFWwindow* getGlfwWindow() { return window; }

    graphics::View* get_view() override final { return view; }

    void save_screenshot( std::string name, ImageType imageType ) override final {
      std::string path = name;
      int channelCount;

      switch ( imageType ) {
        case IMAGE_JPG:
          channelCount = 3;
          path += ".jpg";
          break;
        case IMAGE_PNG:
          channelCount = 4;
          path += ".png";
          break;
        case IMAGE_BMP:
          channelCount = 3;
          path += ".bmp";
          break;
        default:
          std::string error = "WindowGlfw.save_screenshot: unknown image type for \"" + path + "\"";
          throw std::exception( error.c_str() );
      }

      int n = channelCount * width * height;
      GLubyte* pixels = new GLubyte[n];

      glReadPixels( 0, 0, width, height, ( channelCount == 3 ) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels );

      cimg_library::CImg<GLubyte> screenshot( width, height, 1, channelCount );
      GLubyte* ptr = screenshot.data( 0, 0, 0, 0 );

      for ( int x = 0; x < width; x++ ) {
        for ( int y = 0; y < height; y++ ) {
          for ( int c = 0; c < channelCount; c++ ) {
            ptr[c*width*height + y*width + x] = pixels[channelCount * ( height - 1 - y )*width + channelCount * x + c];
          }
        }
      }

      switch ( imageType ) {
        case IMAGE_JPG:
          screenshot.save_jpeg( path.c_str() );
          break;
        case IMAGE_PNG:
          screenshot.save_png( path.c_str() );
          break;
        case IMAGE_BMP:
          screenshot.save_bmp( path.c_str() );
          break;
      }
    }

    private:
    void create_glfw_window( bool isFullscreen ) {
      this->isFullscreen = isFullscreen;

      if ( window != nullptr ) {
        glfwDestroyWindow( window );
      }

      glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
      window = glfwCreateWindow( this->width, this->height, title.c_str(), ( isFullscreen ) ? glfwGetPrimaryMonitor() : nullptr, nullptr );
      view->get_rectangle()->set_size( this->width, this->height );

      const WindowGlfw* me = this;

      // TODO: Link to keyboard.
      glfwSetWindowUserPointer( window, this );
      glfwSetKeyCallback( window, [] ( GLFWwindow* window, int key, int scancode, int action, int mods ) {
        input::IKeyboard* keyboard = IApp::instance()->get_input()->getKeyboard();
        IWindow* w = (IWindow*) glfwGetWindowUserPointer( window );

        if ( action == GLFW_PRESS ) {
          if ( key == GLFW_KEY_ESCAPE ) {
            w->toggle_fullscreen();
          } else if ( key == GLFW_KEY_F1 ) {
            w->save_screenshot( "img", IMAGE_JPG );
          }
          keyboard->handle( key, PRESSABLESTATE_PRESSED );
        } else if ( action == GLFW_RELEASE ) {
          keyboard->handle( key, PRESSABLESTATE_RELEASED );
        }
      } );
    }

    std::string title = "";
    GLFWwindow *window = nullptr;
    int width = 640, height = 480;
    bool isFullscreen;
    graphics::View* view;
  };
}
