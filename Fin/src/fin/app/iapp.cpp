#include "stdafx.h"
#include "iapp.h"
#include "actor/iactor.h"

namespace fin::app {
  IApp* IApp::_instance = nullptr;

  IApp::IApp() {
    _instance = this;
  }

  void IApp::tick() {
    // TODO: Presort these to limit loops...???

    IActor::tick_all( this );
  }

  void IApp::render() {
    get_main_window()->render( get_graphics(), this );
  }
}
