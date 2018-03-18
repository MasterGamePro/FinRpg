#pragma once

#pragma once

#include "fin/input/keypressableinput.h"
#include "fin/input/pressableinputdirectionalinput.h"
#include "imoderninputlayout.h"

namespace fin::input {

  class GamepadModernInputLayout : public IModernInputLayout {
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
      * primaryDirectionalInput = new AnalogStickDirectionalInput(),
      *secondaryDirectionalInput = new AnalogStickDirectionalInput();
    IPressableInput
      *actionPressableInput, // = new KeyPressableInput(KEYCODE_U),
      *cancelPressableInput; // = new KeyPressableInput(KEYCODE_H);
  };
}