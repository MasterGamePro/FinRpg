#pragma once
#include "keyboardglfw.h"
#include "fin/input/iinput.h"

namespace fin::input {
  class InputGlfw : public IInput {
    public:
    IKeyboard* getKeyboard() override final {
      return keyboard;
    }

    private:
    KeyboardGlfw* keyboard = new KeyboardGlfw();
  };
}
