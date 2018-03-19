#pragma once

namespace fin::input {
  class IDirectionalInput {
    public:
    virtual ~IDirectionalInput() {}

    virtual double get_pressed_amount() const = 0;
    virtual double get_pressed_direction() const = 0;

    virtual double getHeldAmount() const = 0;
    virtual double getHeldDirection() const = 0;
  };
}