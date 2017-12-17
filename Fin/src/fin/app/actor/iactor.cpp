#include "stdafx.h"
#include "iactor.h"
#include "fin/debug/memory.h"

namespace fin::app {
  data::HashSet<IActor*> IActor::toplevelInstances;

  IActor::IActor() {
    debug::totalBytes += sizeof( IActor );
    toplevelInstances.add( this );
  }
  IActor::~IActor() {
    debug::totalBytes -= sizeof( IActor );
  }
}