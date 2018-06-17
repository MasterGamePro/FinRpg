#pragma once

namespace fin::input {
  enum class PressableState {
    UP, DOWN,
    PRESSED, RELEASED
  };

  bool check_pressable_state(PressableState actualState, PressableState expectedState);
}