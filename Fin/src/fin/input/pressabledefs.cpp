#include "stdafx.h"
#include "pressabledefs.h"

namespace fin::input {
  bool check_pressable_state(PressableState actualState, PressableState expectedState) {
    if (actualState == PressableState::RELEASED && expectedState == PressableState::UP) { return true; }
    if (actualState == PressableState::PRESSED && expectedState == PressableState::DOWN) { return true; }
    return actualState == expectedState;
  }
}