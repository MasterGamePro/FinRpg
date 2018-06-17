#include "stdafx.h"

#include "windowglfw.h"

namespace fin::app {
  WindowGlfw::WindowGlfw(graphics::GraphicsGl* g) : g_(g) {
    view = new graphics::View();
    create_glfw_window(false);
  }

  WindowGlfw::~WindowGlfw() {
    delete view;
    if (window != nullptr) { glfwDestroyWindow(window); }
  }

  void WindowGlfw::create_glfw_window(bool isFullscreen) {
    this->isFullscreen = isFullscreen;

    if (window != nullptr) { glfwDestroyWindow(window); }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(this->width, this->height, title.c_str(),
                              (isFullscreen)
                                ? glfwGetPrimaryMonitor()
                                : nullptr, nullptr);
    view->get_rectangle()->set_size(this->width, this->height);

    // TODO: Link to keyboard.
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window,
                       [](GLFWwindow* window, int key, int scancode,
                          int action, int mods) {
                         input::IKeyboard* keyboard = IApp::instance()->
                           get_input()->get_keyboard();
                         IWindow* w = (IWindow*)
                           glfwGetWindowUserPointer(window);

                         if (action == GLFW_PRESS) {
                           if (key == GLFW_KEY_ESCAPE) { w->close(); }
                           else if (key == GLFW_KEY_T) {
                             w->toggle_fullscreen();
                           }
                           else if (key == GLFW_KEY_F1) {
                             w->save_screenshot("img", image::IMAGEFILE_JPG);
                           }
                           keyboard->
                             handle(key, input::PressableState::PRESSED);
                         }
                         else if (action == GLFW_RELEASE) {
                           keyboard->
                             handle(key, input::PressableState::RELEASED);
                         }
                       });
    //glfwSetCursorPosCallback(window, []();
    //glfwSetMouseButtonCallback() {}
    //glfwSetScrollCallback(window, []);
    //glfwSetDropCallback();

    // When fullscreen is toggled, GL context is lost. Must manually reset 
    // default settings and reload textures.
    //g->reloadContext();
  }
}
