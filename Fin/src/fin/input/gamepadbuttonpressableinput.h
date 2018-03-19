#pragma once
#include "igamepad.h"
#include "ipressableinput.h"

namespace fin::input {
  class GamepadButtonPressableInput : public IPressableInput {
    public:
    GamepadButtonPressableInput(IGamepad* gamepad, int buttonIndex) : gamepad(gamepad),
      buttonIndex(buttonIndex) {}

    PressableState get_state() const override final {
      return gamepad->get_button_state(buttonIndex);
    }

    private:
    const IGamepad* gamepad;
    const int buttonIndex;
  };
}
