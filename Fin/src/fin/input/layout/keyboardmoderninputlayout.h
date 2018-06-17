#pragma once

#include "fin/input/keypressableinput.h"
#include "fin/input/pressableinputdirectionalinput.h"
#include "imoderninputlayout.h"

namespace fin::input {
  class KeyboardModernInputLayout : public IModernInputLayout {
    public:
    KeyboardModernInputLayout(IKeyboard* keyboard) {
      primaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(keyboard, Keycode::A),
        new KeyPressableInput(keyboard, Keycode::D),
        new KeyPressableInput(keyboard, Keycode::W),
        new KeyPressableInput(keyboard, Keycode::S));
      secondaryDirectionalInput = new PressableInputDirectionalInput(
        new KeyPressableInput(keyboard, Keycode::K),
        new KeyPressableInput(keyboard, Keycode::SEMICOLON),
        new KeyPressableInput(keyboard, Keycode::O),
        new KeyPressableInput(keyboard, Keycode::L));
      actionPressableInput = new KeyPressableInput(keyboard, Keycode::U);
      cancelPressableInput = new KeyPressableInput(keyboard, Keycode::H);
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
