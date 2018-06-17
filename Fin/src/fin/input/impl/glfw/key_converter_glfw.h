#pragma once

#include "fin/input/ikeyconverter.h"
#include "fin/input/keyboard_defs.h"

namespace fin::input {
  class KeyConverterGlfw : public IKeyConverter {
    public:
    Keycode get_keycode(int library_key) override final;
    int get_tkeycode(Keycode key_code) override final;
  };
}
