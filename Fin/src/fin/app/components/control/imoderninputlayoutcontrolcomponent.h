#pragma once
#include "fin/input/iinput.h"
#include "icontrolcomponent.h"

namespace fin::app {
  class IModernInputLayoutControlComponent : public IControlComponent {
    public:
    virtual void tick_control(input::IModernInputLayout* inputLayout) = 0;

    void tick_control(input::IInput* input) override final {
      tick_control(input->get_input_layout());
    }
  };
}
