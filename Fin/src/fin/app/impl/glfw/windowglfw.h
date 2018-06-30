#pragma once

#include <boost/algorithm/string.hpp>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#define cimg_use_jpeg
#define cimg_use_png
#define cimg_use_bmp
#include "CImg.h"

#include "fin/app/iwindow.h"
#include "fin/graphics/view.h"
#include "fin/graphics/impl/gl/graphicsgl.h"
#include <boost/asio/detail/bind_handler.hpp>

namespace fin::app {
  class AppGlfw;

  class WindowGlfw : public IWindow {
    public:
    WindowGlfw(graphics::GraphicsGl* g);
    ~WindowGlfw();

    void set_title(std::string title) override final {
      this->title = title;
      glfwSetWindowTitle(window, title.c_str());
    };

    // TODO: Apply size/fullscreen change in a single method?
    void set_size(int width, int height) override final {
      if (this->width != width || this->height != height) {
        this->width = width;
        this->height = height;
        view->get_rectangle()->set_size(width, height);
        if (!isFullscreen_) { glfwSetWindowSize(window, width, height); }
        else {
          create_glfw_window(isFullscreen_);
          checkReloadContext = true;
        }
      }
    }

    void set_position(int x, int y) override final {
      glfwSetWindowPos(window, x, y);
    }

    void show() override final { glfwShowWindow(window); }
    void hide() override final { glfwHideWindow(window); }

    bool is_closed() override final { return glfwWindowShouldClose(window); }
    void close() override final { glfwSetWindowShouldClose(window, true); }

    bool is_fullscreen() override final { return isFullscreen_; }

    void toggle_fullscreen(const bool isFullscreen) override final {
      if (isFullscreen != isFullscreen_) {
        create_glfw_window(isFullscreen);
        checkReloadContext = true;
      }
    }

    void render(graphics::IGraphics* g, IApp* app) override final {
      glfwMakeContextCurrent(window);

      const auto newContext = wglGetCurrentContext();
      if (checkReloadContext) {
        g_->reload_context();
        checkReloadContext = false;
      }
      context = newContext;

      IWindow::render(g, app);

      const auto t = g->t();
      t->set_target_matrix(graphics::MatrixType::PROJECTION);
      t->identity();
      t->ortho(0, 0 + width, 0 + height, 0, -1, 1000);
      g->rt()->draw_string(algorithm::format_string("%d (%d)", app->get_fps(),
                                                    app->get_frame()),
                           320, 0);

      glfwSwapBuffers(window);
    }

    GLFWwindow* getGlfwWindow() { return window; }

    graphics::View* get_view() override final { return view; }

    void save_screenshot(std::string name, image::ImageFileType imageType)
    override final {
      std::string path = name;
      int channelCount;

      switch (imageType) {
        case image::IMAGEFILE_JPG:
          channelCount = 3;
          path += ".jpg";
          break;
        case image::IMAGEFILE_PNG:
          channelCount = 4;
          path += ".png";
          break;
        case image::IMAGEFILE_BMP:
          channelCount = 3;
          path += ".bmp";
          break;
        default:
          std::string error =
            "WindowGlfw.save_screenshot: unknown image type for \"" + path +
            "\"";
          throw std::exception(error.c_str());
      }

      int n = channelCount * width * height;
      GLubyte* pixels = new GLubyte[n];

      glReadPixels(0, 0, width, height, (channelCount == 3) ? GL_RGB : GL_RGBA,
                   GL_UNSIGNED_BYTE, pixels);

      cimg_library::CImg<GLubyte> screenshot(width, height, 1, channelCount);
      GLubyte* ptr = screenshot.data(0, 0, 0, 0);

      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          for (int c = 0; c < channelCount; c++) {
            ptr[c * width * height + y * width + x] = pixels[
              channelCount * (height - 1 - y) * width + channelCount * x + c];
          }
        }
      }

      switch (imageType) {
        case image::IMAGEFILE_JPG:
          screenshot.save_jpeg(path.c_str());
          break;
        case image::IMAGEFILE_PNG:
          screenshot.save_png(path.c_str());
          break;
        case image::IMAGEFILE_BMP:
          screenshot.save_bmp(path.c_str());
          break;
      }
    }

    private:
    void create_glfw_window(bool isFullscreen);

    graphics::GraphicsGl* g_;
    std::string title = "";
    GLFWwindow* window = nullptr;
    int width = 640, height = 480;
    bool isFullscreen_;
    graphics::View* view;

    bool checkReloadContext = false;
    HGLRC context;
  };
}
