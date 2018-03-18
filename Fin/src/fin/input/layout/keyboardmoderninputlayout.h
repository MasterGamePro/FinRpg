#pragma once

#include "fin/input/keypressableinput.h"
#include "fin/input/pressableinputdirectionalinput.h"
#include "imoderninputlayout.h"

namespace fin::input {

  class KeyboardModernInputLayout : public IModernInputLayout {

    public:
    const IDirectionalInput* getPrimaryDirectionalInput() override final {
      return primaryDirectionalInput;
    }
    const IDirectionalInput* getSecondaryDirectionalInput() override final {
      return secondaryDirectionalInput;
    }

    const IPressableInput* getActionPressableInput() override final {
      return actionPressableInput;
    }
    const IPressableInput* getCancelPressableInput() override final {
      return cancelPressableInput;
    }

    private:
    IDirectionalInput
      * primaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(KEYCODE_A),
        new KeyPressableInput(KEYCODE_D),
        new KeyPressableInput(KEYCODE_W),
        new KeyPressableInput(KEYCODE_S)),
      *secondaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(KEYCODE_K),
        new KeyPressableInput(KEYCODE_SEMICOLON),
        new KeyPressableInput(KEYCODE_O),
        new KeyPressableInput(KEYCODE_L));
    IPressableInput
      *actionPressableInput = new KeyPressableInput(KEYCODE_U),
      *cancelPressableInput = new KeyPressableInput(KEYCODE_H);
  };
}
