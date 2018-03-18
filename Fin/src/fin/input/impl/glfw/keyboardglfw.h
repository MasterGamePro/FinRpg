#pragma once
#include "fin/input/ikeyboard.h"
#include "keyconverterglfw.h"

namespace fin::input {
  class KeyboardGlfw : public IKeyboard {
    public:
    KeyboardGlfw() : IKeyboard(new KeyConverterGlfw()) {}
  };
}
