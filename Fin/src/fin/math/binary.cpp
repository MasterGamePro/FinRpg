#include "stdafx.h"

#include "binary.h"

namespace fin::math {
  bool xor(const bool a, const bool b) { return (!a && b) || (a && !b); }
}
