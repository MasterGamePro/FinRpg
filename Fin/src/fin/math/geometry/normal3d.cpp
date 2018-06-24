#include "stdafx.h"

#include "normal3d.h"

namespace fin::math {
  Normal3d Normal3d::kUp(0, 0, 1);

  Normal3d& Normal3d::operator+=(const Normal3d& other) {
    x_ += other.x();
    y_ += other.y();
    z_ += other.z();
    return *this;
  }
}
