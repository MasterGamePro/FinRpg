#pragma once
#include "ikeyboard.h"
#include "layout/imoderninputlayout.h"
#include "layout/keyboardmoderninputlayout.h"
#include "igamepad.h"

namespace fin::input {
  class IInput {
    public:
    IInput() { _instance = this; }
    virtual ~IInput() {}

    virtual IKeyboard* get_keyboard() const = 0;
    //virtual IMouse* getMouse() = 0;
    virtual const data::IList<IGamepad*>* get_gamepads() const = 0;
    virtual IModernInputLayout* get_input_layout() const = 0;

    virtual void poll() = 0;

    void before_tick() {
      get_keyboard()->before_tick();
      get_gamepads()->const_iterate([](IGamepad* gamepad, int i) {
        gamepad->before_tick();
      });
    }

    void after_tick() {
      get_keyboard()->after_tick();
      get_gamepads()->const_iterate([] (IGamepad* gamepad, int i) {
        gamepad->after_tick();
      });
    }

    static IInput* instance() { return _instance; }

    private:
    static IInput* _instance;
  };
}
