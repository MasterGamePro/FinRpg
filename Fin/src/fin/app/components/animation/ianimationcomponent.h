#pragma once

#include "../icomponent.h"

namespace fin::app {
  class IAnimationComponent : public IComponent {
  public:
    ComponentType get_type() final {
      return COMPONENT_ANIMATION;
    };

    virtual void tick_animation() = 0;
  };
}