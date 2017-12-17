#include "stdafx.h"

#include "../igraphics.h"
#include "camera.h"
#include "fin/math/geometry/normal3d.h"

namespace fin::graphics {
  void Camera::render(IGraphics* g) const {
    ITransform* t = g->t();
    IScreen* s = g->s();

    t->set_target_matrix(MATRIX_PROJECTION);
    t->push_matrix();

    math::TreeRectangle* rectangle = s->get_clip_rectangle();
    const double
      x = rectangle->get_absolute_x(),
      y = rectangle->get_absolute_y(),
      width = rectangle->get_clipped_width(),
      height = rectangle->get_clipped_height();

    t->identity();
    t->perspective(fieldOfView, width / height, 1, 1000);
    t->look_at(fromPoint, toPoint, math::Normal3d::UP);
    stage->tick_render_perspective(g);

    t->set_target_matrix(MATRIX_PROJECTION);
    t->identity();
    t->ortho(x, x + width, y + height, y, -1, 1000);
    stage->tick_render_ortho(g);

    t->set_target_matrix(MATRIX_PROJECTION);
    t->pop_matrix();
  }
}
