#pragma once
#include "fin/input/gamepadanalogdirectionalinput.h"
#include "fin/input/gamepadbuttonpressableinput.h"
#include "fin/input/igamepad.h"
#include "imoderninputlayout.h"

namespace fin::input {
  class GamepadModernInputLayout : public IModernInputLayout {
    public:
    GamepadModernInputLayout(IGamepad* gamepad) {
      primaryDirectionalInput = new GamepadAnalogDirectionalInput(gamepad, 0, 1);
      secondaryDirectionalInput = new GamepadAnalogDirectionalInput(gamepad, 2, 3);
      actionPressableInput = new GamepadButtonPressableInput(gamepad, 1);
      cancelPressableInput = new GamepadButtonPressableInput(gamepad, 0);
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
    IDirectionalInput * primaryDirectionalInput, *secondaryDirectionalInput;
    IPressableInput *actionPressableInput, *cancelPressableInput;
  };
}
