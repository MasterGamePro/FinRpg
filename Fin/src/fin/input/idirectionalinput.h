#pragma once

namespace fin::input {
  class IDirectionalInput {
    public:
    virtual double get_pressed_amount() = 0;
    virtual double getPressedDirection() = 0;

    virtual double getHeldAmount() = 0;
    virtual double getHeldDirection() = 0;
  };
}