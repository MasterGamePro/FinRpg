#pragma once
#include "fin/input/idirectionalinput.h"
#include "fin/input/KeyPressableInput.h"
#include "fin/input/pressableinputdirectionalinput.h"

namespace fin::input {

  class ModernInputLayout {

    public:
    IDirectionalInput* getPrimaryDirectionalInput() { return primaryDirectionalInput; }
    IDirectionalInput* getSecondaryDirectionalInput() { return secondaryDirectionalInput; }

    IPressableInput* getActionPressableInput() { return actionPressableInput; }
    IPressableInput* getCancelPressableInput() { return cancelPressableInput; }

    private:
    IDirectionalInput
      *primaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput( KEYCODE_A ),
        new KeyPressableInput( KEYCODE_D ),
        new KeyPressableInput( KEYCODE_W ),
        new KeyPressableInput( KEYCODE_S ) ),
      *secondaryDirectionalInput;
    IPressableInput
      *actionPressableInput,
      *cancelPressableInput;
  };
}
