#include "stdafx.h"

#include "iwindow.h"
#include "fin/graphics/view.h"

namespace fin::app {
  void IWindow::render( graphics::IGraphics* g, IApp* app ) {
    get_view()->render( g );
  }
}