#pragma once

#include "fin/app/components/icomponent.h"

namespace fin::app {
  class IPhysicsComponent : IComponent {
    public:
    virtual void tick_physics() = 0;
  };
}
