#pragma once
#include "fin/app/actor/iactor.h"

namespace fin::app {
  class IFractionalStatus : public IActor {

    public:
    virtual void set_min( double min ) = 0;
    virtual void set_value( double value ) = 0;
    virtual void set_max( double max ) = 0;

    virtual double get_min() = 0;
    virtual double get_value() = 0;
    virtual double get_max() = 0;

    virtual double get_fraction() = 0;
  };
}
