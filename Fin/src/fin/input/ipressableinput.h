#pragma once
#include "pressabledefs.h"

namespace fin::input {
  class IPressableInput {
    public:
    virtual PressableState get_state() const = 0;
    bool checkState( PressableState expected_state ) const {
      const PressableState actual_state = get_state();

      if ( actual_state == PressableState::RELEASED && expected_state == PressableState::UP ) { return true; }
      if ( actual_state == PressableState::PRESSED && expected_state == PressableState::DOWN ) { return true; }
      return actual_state == expected_state;
    }
  };
}
