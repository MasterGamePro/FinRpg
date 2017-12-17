#pragma once

#include "fin/common/macros.h"

namespace fin::time {
  class DeltaTime {
    STATIC_CLASS( DeltaTime )

    public:
    static double adjust_velocity( double velocity ) { return velocity; }
  };
}