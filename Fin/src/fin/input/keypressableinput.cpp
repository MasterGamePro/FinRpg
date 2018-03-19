#include "stdafx.h"
#include "keypressableinput.h"
#include "iinput.h"

namespace fin::input {
  PressableState KeyPressableInput::get_state() const {
    return keyboard->get_key_state( watchKey );
  }
}
