#include "stdafx.h"
#include "iactor.h"
#include "fin/debug/memory.h"
#include "fin/common/macros.h"

namespace fin::app {
  data::HashSet<IActor*> IActor::toplevelInstances;

  IActor::IActor() {
    ADD_TO_TOTAL_MEMORY_BASE( IActor );
    toplevelInstances.add( this );
  }
  IActor::~IActor() {
    REMOVE_FROM_TOTAL_MEMORY_BASE( IActor );
  }
}