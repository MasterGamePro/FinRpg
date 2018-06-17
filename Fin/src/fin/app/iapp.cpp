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

    const auto stage = get_main_window()->get_view()->get_camera()->stage;

    const auto input = get_input();
    stage->tick_control(input);
    stage->tick_physics();
    stage->tick_collision();
    stage->tick_animation();
    stage->tick_audio();
  }

  void IApp::render() {
    get_main_window()->render(get_graphics(), this);
  }
}
