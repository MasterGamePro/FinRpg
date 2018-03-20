#pragma once

namespace fin::input {
  class ILinearInput {
    public:
    virtual ~ILinearInput() {}

    virtual double get_pressed_amount() const = 0;
    virtual double get_pressed_direction() const = 0;

    virtual double get_held_amount() const = 0;
    virtual double get_held_direction() const = 0;
  };
}