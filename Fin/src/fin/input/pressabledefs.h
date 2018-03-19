#pragma once

namespace fin::input {
  enum PressableState {
    PRESSABLESTATE_UP, PRESSABLESTATE_DOWN,
    PRESSABLESTATE_PRESSED, PRESSABLESTATE_RELEASED
  };

  bool check_pressable_state(PressableState actualState, PressableState expectedState);
}