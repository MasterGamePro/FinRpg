#pragma once

#include "fin/app/components/icomponent.h"

namespace fin::app {
  class ICollisionComponent : IComponent {
    public:
    virtual void tick_collision() = 0;
  };
}
