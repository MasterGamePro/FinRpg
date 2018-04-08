#pragma once
#include "fin/input/layout/gamepadmoderninputlayout.h"
#include "fin/input/layout/keyboardmoderninputlayout.h"
#include "fin/input/iinput.h"
#include "gamepadglfw.h"
#include "keyboardglfw.h"

namespace fin::input {
  class InputGlfw : public IInput {
    public:
    InputGlfw() {
      keyboard = new KeyboardGlfw();
      gamepads = new data::StlVector<IGamepad*>();
      gamepads->push_back(new GamepadGlfw(0));
      //layout = new GamepadModernInputLayout(gamepads->at(0));
      layout = new KeyboardModernInputLayout(keyboard);
    }

    ~InputGlfw() {
      delete keyboard;
      delete layout;
    }

    IKeyboard* get_keyboard() const override final { return keyboard; }
    const data::IList<IGamepad*>* get_gamepads() const override final { return gamepads; };
    IModernInputLayout* get_input_layout() const override final { return layout; }

    void poll() override final {
      gamepads->iterate([](IGamepad* gamepad, int i) {
        gamepad->poll();
      });
    }

    private:
    KeyboardGlfw * keyboard;
    data::StlVector<IGamepad*>* gamepads;
    IModernInputLayout * layout;
  };
}
