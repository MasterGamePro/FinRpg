#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstdio>
#include "fin/app/iapp.h"
#include "windowglfw.h"
#include "fin/input/impl/glfw/inputglfw.h"
#include "fin/graphics/impl/gl/graphicsgl.h"

namespace fin::app {
  class AppGlfw : public IApp {
    public:
    AppGlfw() {
      input = new input::InputGlfw();
      graphics = new graphics::GraphicsGl();
    }

    input::IInput* get_input() const override final { return input; }
    audio::IAudio* get_audio() const override final { return audio; }
    graphics::IGraphics* get_graphics() const override final {
      return graphics;
    };

    void init() override final {
      if (!glfwInit()) { throw std::exception("Failed to init glfw.\n"); }

      window = new WindowGlfw(graphics);

      glewExperimental = GL_FALSE;
      glfwMakeContextCurrent(window->getGlfwWindow());
      if (glewInit() != GLEW_OK) {
        throw std::exception("AppGlfw.init: glewInit failed");
      }
    }

    void deinit() override final { glfwTerminate(); }

    IWindow* get_main_window() override final { return window; }

    protected:
    void poll_inputs() override final {
      glfwPollEvents();
      input->poll();
    }

    private:
    audio::IAudio* audio;
    graphics::IGraphics* graphics;
    input::IInput* input;
    WindowGlfw* window;
  };
}
