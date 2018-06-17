#pragma once
#include "fin/input/igamepad.h"

namespace fin::input {
  class GamepadGlfw : public IGamepad {
    public:
    GamepadGlfw(const GLuint gamepadIndex) {
      this->gamepadIndex = GLFW_JOYSTICK_1 + gamepadIndex;
    }

    void poll() override final {
      int buttonCount;
      const unsigned char* buttons = glfwGetJoystickButtons(gamepadIndex, &buttonCount);
      for (auto buttonIndex = 0; buttonIndex < buttonCount; ++buttonIndex) {
        PressableState buttonState = buttons[buttonIndex] == GLFW_PRESS ?
          PressableState::PRESSED : PressableState::RELEASED;
        handle_button(buttonIndex, buttonState);
      }

      int axisCount;
      const float* axes = glfwGetJoystickAxes(gamepadIndex, &axisCount);
      for (auto axisIndex = 0; axisIndex < axisCount; ++axisIndex) {
        handle_axis(axisIndex, axes[axisIndex]);
      }
    }

    private:
    GLuint gamepadIndex;
  };
}
