#pragma once
#include "ipressableinput.h"
#include "keyboarddefs.h"
#include "ikeyboard.h"

namespace fin::input {
  class KeyPressableInput : public IPressableInput {
    public:
    KeyPressableInput(IKeyboard* keyboard, const Keycode watchKey) {
      this->keyboard = keyboard;
      this->watchKey = watchKey;
    }

    PressableState get_state() const override final;

    private:
    IKeyboard * keyboard;
    Keycode watchKey;
  };
}
