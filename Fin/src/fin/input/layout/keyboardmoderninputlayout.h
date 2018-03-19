#pragma once

#include "fin/input/keypressableinput.h"
#include "fin/input/pressableinputdirectionalinput.h"
#include "imoderninputlayout.h"

namespace fin::input {
  class KeyboardModernInputLayout : public IModernInputLayout {
    public:
    KeyboardModernInputLayout(IKeyboard* keyboard) {
      primaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(keyboard, KEYCODE_A),
        new KeyPressableInput(keyboard, KEYCODE_D),
        new KeyPressableInput(keyboard, KEYCODE_W),
        new KeyPressableInput(keyboard, KEYCODE_S));
      secondaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(keyboard, KEYCODE_K),
        new KeyPressableInput(keyboard, KEYCODE_SEMICOLON),
        new KeyPressableInput(keyboard, KEYCODE_O),
        new KeyPressableInput(keyboard, KEYCODE_L));
      actionPressableInput = new KeyPressableInput(keyboard, KEYCODE_U);
      cancelPressableInput = new KeyPressableInput(keyboard, KEYCODE_H);
    }

    ~KeyboardModernInputLayout() {
      delete primaryDirectionalInput;
      delete secondaryDirectionalInput;
      delete actionPressableInput;
      delete cancelPressableInput;
    }

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
      * primaryDirectionalInput,
      *secondaryDirectionalInput;
    IPressableInput
      *actionPressableInput,
      *cancelPressableInput;
  };
}
