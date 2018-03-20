#pragma once
#include <valarray>
#include <math.h>
#include "fin/math/trig.h"
#include "igamepad.h"
#include "idirectionalinput.h"

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

    double get_held_amount() const override final {
      const auto xAxisState = gamepad->get_axis_state(xAxisIndex),
        yAxisState = gamepad->get_axis_state(yAxisIndex);
      double xEdgeDis, yEdgeDis;
      if (abs(xAxisState) > abs(yAxisState)) {
        xEdgeDis = 1;
        yEdgeDis = yAxisState / xAxisState;
      }
      else {
        xEdgeDis = xAxisState / yAxisState;
        yEdgeDis = 1;
      }
      const double heldAmt = sqrt(xAxisState * xAxisState + yAxisState * yAxisState),
        edgeDis = sqrt(xEdgeDis*xEdgeDis + yEdgeDis * yEdgeDis);
      return heldAmt / edgeDis;
    }
    double get_held_direction() const override final {
      const auto xAxisState = gamepad->get_axis_state(xAxisIndex),
        yAxisState = gamepad->get_axis_state(yAxisIndex);
      return std::atan2(-yAxisState, xAxisState) * math::Trig::kRad2Deg;
    }

    private:
    const IGamepad* gamepad;
    const int xAxisIndex, yAxisIndex;
  };
}
