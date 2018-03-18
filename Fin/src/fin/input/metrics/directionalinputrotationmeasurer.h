#pragma once

namespace fin::input {
  class DirectionalInputRotationMeasurer {
    public:
    double get_pressed_angular_velocity();
    double get_held_angular_velocity();
  };
}