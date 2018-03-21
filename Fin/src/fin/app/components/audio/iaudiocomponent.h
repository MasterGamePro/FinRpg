#pragma once

#include "../icomponent.h"

namespace fin::app {
  class IAudioComponent : public IComponent {
    public:
    ComponentType get_type() final {
      return COMPONENT_AUDIO;
    };

    virtual void tick_audio() = 0;
  };
}