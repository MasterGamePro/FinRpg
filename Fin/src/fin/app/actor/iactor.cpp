#include "stdafx.h"
#include "iactor.h"

namespace fin::app {
  data::HashSet<IActor*> IActor::toplevelInstances;
}