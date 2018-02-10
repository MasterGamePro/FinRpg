#pragma once
#include "KeyPressableInput.h"
#include "idirectionalinput.h"
#include <valarray>
#include "fin/math/binary.h"
#include "fin/math/trig.h"

namespace fin::input {
  class PressableInputDirectionalInput : public IDirectionalInput {
  public:
    PressableInputDirectionalInput(IPressableInput* leftPressableInput,
      IPressableInput* rightPressableInput,
      IPressableInput* upPressableInput,
      IPressableInput* downPressableInput) {
      this->leftPressableInput = leftPressableInput;
      this->rightPressableInput = rightPressableInput;
      this->upPressableInput = upPressableInput;
      this->downPressableInput = downPressableInput;
    }

    double get_pressed_amount() override final {
      const bool isHeld =
        math::Binary:: xor (leftPressableInput->checkState(PRESSABLESTATE_PRESSED),
          rightPressableInput->checkState(PRESSABLESTATE_PRESSED))
        ||
        math::Binary:: xor (upPressableInput->checkState(PRESSABLESTATE_PRESSED),
          downPressableInput->checkState(PRESSABLESTATE_PRESSED));
      return (isHeld) ? 1 : 0;
    }
    double getPressedDirection()  override final {
      const int left = leftPressableInput->checkState(PRESSABLESTATE_PRESSED),
        right = rightPressableInput->checkState(PRESSABLESTATE_PRESSED),
        up = upPressableInput->checkState(PRESSABLESTATE_PRESSED),
        down = downPressableInput->checkState(PRESSABLESTATE_PRESSED);

      return std::atan2(up - down, right - left) * math::Trig::kRad2Deg;
    }

    double getHeldAmount()  override final {
      const bool isHeld =
        math::Binary:: xor (leftPressableInput->checkState(PRESSABLESTATE_DOWN),
          rightPressableInput->checkState(PRESSABLESTATE_DOWN))
        ||
        math::Binary:: xor (upPressableInput->checkState(PRESSABLESTATE_DOWN),
          downPressableInput->checkState(PRESSABLESTATE_DOWN));
      return (isHeld) ? 1 : 0;
    }
    double getHeldDirection() override final {
      const int left = leftPressableInput->checkState(PRESSABLESTATE_DOWN),
        right = rightPressableInput->checkState(PRESSABLESTATE_DOWN),
        up = upPressableInput->checkState(PRESSABLESTATE_DOWN),
        down = downPressableInput->checkState(PRESSABLESTATE_DOWN);

      return std::atan2(up - down, right - left) * math::Trig::kRad2Deg;
    }

  private:
    IPressableInput
      * leftPressableInput,
      *rightPressableInput,
      *upPressableInput,
      *downPressableInput;
  };
}
