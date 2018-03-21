#pragma once

namespace fin::app {
  enum ComponentType {
    COMPONENT_CONTROL,
    COMPONENT_PHYSICS,
    COMPONENT_COLLISION,
    COMPONENT_ANIMATION,
    COMPONENT_AUDIO,
    COMPONENT_RENDER
  };

  class IComponent {
    public:
    virtual ~IComponent() = default;

    //virtual ComponentType get_type() = 0;
    private:
  };
}