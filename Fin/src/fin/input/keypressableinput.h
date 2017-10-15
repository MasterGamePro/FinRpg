#pragma once
#include "ipressableinput.h"
#include "keydefs.h"

namespace fin::input {
  class KeyPressableInput : public IPressableInput {
    public:
    KeyPressableInput( Keycode watchKey ) {
      this->watchKey = watchKey;
    }

    PressableState getState() override final;

    private:
    Keycode watchKey;
  };
}
