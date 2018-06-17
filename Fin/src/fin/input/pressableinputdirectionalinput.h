#pragma once

#include "fin/math/binary.h"
#include "fin/math/trig.h"
 
#include "idirectionalinput.h"

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

    double get_pressed_amount() const override final {
      return calc_amount_in_state(PressableState::PRESSED);
    }
    double get_pressed_direction() const override final {
      return calc_direction_in_state(PressableState::PRESSED);
    }

    double get_held_amount() const override final {
      return calc_amount_in_state(PressableState::DOWN);
    }
    double get_held_direction() const override final {
      return calc_direction_in_state(PressableState::DOWN);
    }

    private:
    double calc_amount_in_state(const PressableState& state) const {
      return math::xor(leftPressableInput->checkState(state),
                       rightPressableInput->checkState(state)) ||
             math::xor(upPressableInput->checkState(state),
                       downPressableInput->checkState(state))
               ? 1
               : 0;
    }

    double calc_direction_in_state(const PressableState& state) const {
      const int left = leftPressableInput->checkState(state),
        right = rightPressableInput->checkState(state),
        up = upPressableInput->checkState(state),
        down = downPressableInput->checkState(state);
      return std::atan2(up - down, right - left) * math::kRad2Deg;
    }

    IPressableInput
      *leftPressableInput,
      *rightPressableInput,
      *upPressableInput,
      *downPressableInput;
  };
}
