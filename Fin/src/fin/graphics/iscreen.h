#pragma once
#include "fin/math/shapes/irectangle.h"
#include "fin/data/collections/stack/stlstack.h"
#include "fin/math/shapes/treerectangle.h"
#include "fin/debug/log.h"

namespace fin::graphics {
  class IScreen {
    public:
    virtual ~IScreen() {}

    virtual void clear() = 0;
    virtual void clear_color3d(double r, double g, double b) = 0;
    virtual void clear_color4d(double r, double g, double b, double a) = 0;

    void begin_viewport(math::TreeRectangle* rectangle) {
      math::TreeRectangle* copy = new math::TreeRectangle();
      copy->set_bounds(rectangle->get_x(), rectangle->get_y(),
                       rectangle->get_width(), rectangle->get_height());

      if (viewportStack.size() > 0) {
        copy->attach_to(viewportStack.peek());
      }

      viewportStack.push(copy);
      update_viewport(copy);
    }

    void end_viewport() {
      math::TreeRectangle* back = viewportStack.peek();
      back->detach();
      delete back;

      viewportStack.pop();
      if (viewportStack.size() > 0) {
        update_viewport(viewportStack.peek());
      }
    }

    math::TreeRectangle* get_clip_rectangle() { return viewportStack.peek(); }

    protected:
    virtual void update_viewport(math::TreeRectangle* rectangle) = 0;

    private:
    data::StlStack<math::TreeRectangle*> viewportStack;
  };
}
