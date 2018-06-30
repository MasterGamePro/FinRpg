#include "stdafx.h"

#include "fin/graphics/view.h"
#include "actor/iactor.h"
#include "iwindow.h"

#include "iapp.h"

namespace fin::app {
  IApp* IApp::instance_ = nullptr;

  IApp::IApp() {
    instance_ = this;
    scene_ = nullptr;
    next_scene_ = nullptr;
  }

  void IApp::tick() {
    // TODO: Presort these to limit loops...???

    const auto view = get_main_window()->get_view();
    if (view != nullptr) {
      const auto camera = view->get_camera();
      if (camera != nullptr) {
        const auto stage = camera->stage;
        if (stage != nullptr) {
          stage->tick_control(get_input());
          stage->tick_physics();
          stage->tick_collision();
          stage->tick_animation();
          stage->tick_audio();
        }
      }
    }
  }

  void IApp::render() { get_main_window()->render(get_graphics(), this); }
}
