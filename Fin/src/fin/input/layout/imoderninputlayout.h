#pragma once

#include "fin/input/idirectionalinput.h"
#include "fin/input/ipressableinput.h"

namespace fin::input {

  class IModernInputLayout {

    public:
    virtual const IDirectionalInput* getPrimaryDirectionalInput() = 0;
    virtual const IDirectionalInput* getSecondaryDirectionalInput() = 0;

    virtual const IPressableInput* getActionPressableInput() = 0;
    virtual const IPressableInput* getCancelPressableInput() = 0;
  };
}
