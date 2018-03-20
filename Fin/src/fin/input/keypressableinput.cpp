#include "stdafx.h"
#include "iinput.h"
#include "keypressableinput.h"

namespace fin::input {
  PressableState KeyPressableInput::get_state() const {
    return keyboard->get_key_state( watchKey );
  }
}
