#include "stdafx.h"
#include "keypressableinput.h"
#include "iinput.h"

namespace fin::input {
  PressableState KeyPressableInput::getState() const {
    return input::IInput::instance()->getKeyboard()->get_key_state( watchKey );
  }
}
