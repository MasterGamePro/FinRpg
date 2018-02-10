#pragma once
#include "pressabledefs.h"

namespace fin::input {
  class IPressableInput {
    public:
    virtual PressableState getState() const = 0;
    bool checkState( PressableState expected_state ) const {
      const PressableState actual_state = getState();

      if ( actual_state == PRESSABLESTATE_RELEASED && expected_state == PRESSABLESTATE_UP ) { return true; }
      if ( actual_state == PRESSABLESTATE_PRESSED && expected_state == PRESSABLESTATE_DOWN ) { return true; }
      return actual_state == expected_state;
    }
  };
}
