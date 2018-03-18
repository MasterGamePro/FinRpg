#pragma once
#include "ikeyboard.h"
#include "layout/imoderninputlayout.h"
#include "layout/keyboardmoderninputlayout.h"

namespace fin::input {
  class IInput {
    public:
    IInput() { _instance = this; }
    virtual ~IInput() {}

    virtual IKeyboard* getKeyboard() = 0;
    //virtual IMouse* getMouse() = 0;
    IModernInputLayout* getInputLayout() const { return layout; }

    static IInput* instance() { return _instance; }

    private:
    IModernInputLayout * layout = new KeyboardModernInputLayout();
    static IInput* _instance;
  };
}
