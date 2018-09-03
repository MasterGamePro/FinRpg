#pragma once
#include "fin/app/components/control/icontrolcomponent.h"
#include "fin/input/iinput.h"

namespace fin {
  namespace app {
    class PositionData3d;
  }
}

namespace rpg::characters {
  class NpcWanderControlComponent : public fin::app::IControlComponent {
    public:
    // TODO: Can we access via & rather than *?
    explicit NpcWanderControlComponent(fin::app::PositionData3d* )

    void tick_control(fin::input::IInput* input) override final {
      
    }
  };
}
