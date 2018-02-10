#include "stdafx.h"
#include "iapp.h"
#include "actor/iactor.h"

namespace fin::app {
  IApp* IApp::instance_ = nullptr;

  IApp::IApp() {
    instance_ = this;
    scene_ = nullptr;
    next_scene_ = nullptr;
  }

  void IApp::tick() {
    // TODO: Presort these to limit loops...???

    IActor::tick_all(this);
  }

  void IApp::render() {
    get_main_window()->render(get_graphics(), this);
  }
}
