#pragma once

namespace fin::input {
  class IDirectionalInput {
    public:
    virtual double getPressedAmount() = 0;
    virtual double getPressedDirection() = 0;

    virtual double getHeldAmount() = 0;
    virtual double getHeldDirection() = 0;
  };
}