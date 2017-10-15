#pragma once
#include "ikeyboard.h"
#include "layout/moderninputlayout.h"

namespace fin::input {
  class IInput {
    public:
    IInput() { _instance = this; }

    virtual IKeyboard* getKeyboard() = 0;
    ModernInputLayout* getInputLayout() const { return layout; }

    static IInput* instance() { return _instance; }

    private:
    ModernInputLayout* layout = new ModernInputLayout();
    static IInput* _instance;
  };
}
