#pragma once
#include "igamepad.h"
#include "idirectionalinput.h"
#include "fin/math/trig.h"
#include <valarray>

namespace fin::input {
  class GamepadAnalogDirectionalInput : public IDirectionalInput {
    public:
    GamepadAnalogDirectionalInput(IGamepad* gamepad, const int xAxisIndex,
                                  const int yAxisIndex) : gamepad(gamepad),
      xAxisIndex(xAxisIndex), yAxisIndex(yAxisIndex) {}

    double get_pressed_amount() const override final {
      return 0;
    }
    double get_pressed_direction() const override final {
      return 0;
    }

    double getHeldAmount() const override final {
      const auto xAxisState = gamepad->get_axis_state(xAxisIndex),
        yAxisState = gamepad->get_axis_state(yAxisIndex);
      return sqrt(xAxisState * xAxisState + yAxisState * yAxisState);
    }
    double getHeldDirection() const override final {
      const auto xAxisState = gamepad->get_axis_state(xAxisIndex),
        yAxisState = gamepad->get_axis_state(yAxisIndex);
      return std::atan2(-yAxisState, xAxisState) * math::Trig::kRad2Deg;
    }

    private:
    const IGamepad* gamepad;
    const int xAxisIndex, yAxisIndex;
  };
}
