#pragma once
#include "fin/app/components/icomponent.h"

namespace fin::app {
  class IControlComponent : IComponent {
    public:
    virtual void tick_control(input::IInput* input) = 0;
  };
}
