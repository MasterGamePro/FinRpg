#include "stdafx.h"
#include "pressabledefs.h"

namespace fin::input {
  bool check_pressable_state(PressableState actualState, PressableState expectedState) {
    if (actualState == PRESSABLESTATE_RELEASED && expectedState == PRESSABLESTATE_UP) { return true; }
    if (actualState == PRESSABLESTATE_PRESSED && expectedState == PRESSABLESTATE_DOWN) { return true; }
    return actualState == expectedState;
  }
}