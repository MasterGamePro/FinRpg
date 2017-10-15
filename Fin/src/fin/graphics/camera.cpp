#include "stdafx.h"
#include "igraphics.h"
#include "camera.h"

namespace fin::graphics {
  void Camera::render( IGraphics* g ) const {
    ITransform* t = g->t();
    IScreen* s = g->s();

    t->set_target_matrix( MATRIX_PROJECTION );
    t->push_matrix();
    if ( projectionType == PROJECTION_ORTHO ) {
      math::TreeRectangle* rectangle = s->get_clip_rectangle();
      const double
        x = rectangle->get_absolute_x(),
        y = rectangle->get_absolute_y(),
        width = rectangle->get_clipped_width(),
        height = rectangle->get_clipped_height();
      t->ortho( x, x + width, y + height, y, -1, 1000 );
    } else if ( projectionType == PROJECTION_PERSPECTIVE ) {

    }

    stage->tick_render( g );

    t->set_target_matrix( MATRIX_PROJECTION );
    t->pop_matrix();
  }
}
