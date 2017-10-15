#include "stdafx.h"
#include "view.h"
#include "fin/debug/exception.h"

namespace fin::graphics {
  void View::render( IGraphics* g ) {
    IScreen* s = g->s();

    if ( s == nullptr ) {
      throw debug::Exception( "View", "render", "IScreen is null" );
    }

    s->begin_viewport( rectangle );
    s->clear();

    camera->render( g );
    s->end_viewport();
  }
}
