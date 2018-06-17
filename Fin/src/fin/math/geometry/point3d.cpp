#include "stdafx.h"

#include "normal3d.h"
#include "point3d.h"

namespace fin::math {
  Normal3d Point3d::operator-(const Point3d& other) const {
    Normal3d normal(x() - other.x(), y() - other.y(), z() - other.z());
    return normal;
  }

  Point3d Point3d::operator+(const Normal3d& other) const {
    Point3d point(x() + other.x(), y() + other.y(), z() + other.z());
    return point;
  }

  Point3d& Point3d::operator+=(const Normal3d& other) {
    x_ += other.x();
    y_ += other.y();
    z_ += other.z();
    return *this;
  }
}
