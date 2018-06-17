#pragma once
#include "fin/input/ikeyboard.h"
#include "key_converter_glfw.h"

namespace fin::input {
  class KeyboardGlfw : public IKeyboard {
    public:
    KeyboardGlfw() : IKeyboard(new KeyConverterGlfw()) {}
  };
}
