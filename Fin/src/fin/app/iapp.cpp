#include "stdafx.h"
#include "iapp.h"
#include "actor/iactor.h"
#include "fin/debug/memory.h"

namespace fin::app {
  IApp* IApp::instance_ = nullptr;

  IApp::IApp() {
    debug::totalBytes += sizeof( IApp );
    instance_ = this;
  }

  IApp::~IApp() {
    debug::totalBytes -= sizeof( IApp );
  }


  void IApp::tick() {
    // TODO: Presort these to limit loops...???

    IActor::tick_all( this );
  }

  void IApp::render() {
    get_main_window()->render( get_graphics(), this );
  }
}
