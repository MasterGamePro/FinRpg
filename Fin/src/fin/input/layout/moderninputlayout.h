#pragma once
#include "fin/input/idirectionalinput.h"
#include "fin/input/KeyPressableInput.h"
#include "fin/input/pressableinputdirectionalinput.h"

namespace fin::input {

  class ModernInputLayout {

    public:
    const IDirectionalInput* getPrimaryDirectionalInput() { return primaryDirectionalInput; }
    const IDirectionalInput* getSecondaryDirectionalInput() { return secondaryDirectionalInput; }

    const IPressableInput* getActionPressableInput() { return actionPressableInput; }
    const IPressableInput* getCancelPressableInput() { return cancelPressableInput; }

    private:
    IDirectionalInput
      * primaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(KEYCODE_A),
        new KeyPressableInput(KEYCODE_D),
        new KeyPressableInput(KEYCODE_W),
        new KeyPressableInput(KEYCODE_S)),
      *secondaryDirectionalInput;
    IPressableInput
      *actionPressableInput = new KeyPressableInput(KEYCODE_U),
      *cancelPressableInput = new KeyPressableInput(KEYCODE_H);
  };
}
