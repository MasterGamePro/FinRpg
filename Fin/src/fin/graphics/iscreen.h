#pragma once
#include "fin/math/shapes/irectangle.h"
#include "fin/data/collections/list/vector.h"
#include "fin/math/shapes/treerectangle.h"
#include "fin/debug/log.h"

namespace fin::graphics {
  class IScreen {
    public:
    virtual void clear() = 0;

    void begin_viewport( math::TreeRectangle* rectangle ) {
      math::TreeRectangle* copy = new math::TreeRectangle();
      copy->set_bounds( rectangle->get_x(), rectangle->get_y(),
                        rectangle->get_width(), rectangle->get_height() );

      if ( viewportStack.size() > 0 ) {
        copy->attach_to( viewportStack.back() );
      }

      viewportStack.pushBack( copy );
      update_viewport( copy );
    }

    void end_viewport() {
      math::TreeRectangle* back = viewportStack.back();
      back->detach();
      delete back;

      viewportStack.popBack();

      if ( viewportStack.size() > 0 ) {
        update_viewport( viewportStack.back() );
      }
    }

    math::TreeRectangle* get_clip_rectangle() { return viewportStack.back(); }

    protected:
    virtual void update_viewport( math::TreeRectangle* rectangle ) = 0;

    private:
    data::Vector<math::TreeRectangle*> viewportStack;
  };
}
