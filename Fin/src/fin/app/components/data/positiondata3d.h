#pragma once
#include "fin/math/geometry/point3d.h"
#include "fin/math/geometry/normal3d.h";

namespace fin::app {
  class PositionData3d {
    public:
    double x() const { return position_.x(); }
    double y() const { return position_.y(); }
    double z() const { return position_.z(); }
    double x(double x) { return position_.x(x); }
    double y(double y) { return position_.y(y); }
    double z(double z) { return position_.z(z); }

    double vX() const { return velocity_.x(); }
    double vY() const { return velocity_.y(); }
    double vZ() const { return velocity_.z(); }
    double vX(const double _vX) { return velocity_.x(_vX); }
    double vY(const double _vY) { return velocity_.y(_vY); }
    double vZ(const double _vZ) { return velocity_.z(_vZ); }

    double aX() const { return acceleration_.x(); }
    double aY() const { return acceleration_.y(); }
    double aZ() const { return acceleration_.z(); }
    double aX(double _aX) { return acceleration_.x(_aX); }
    double aY(double _aY) { return acceleration_.y(_aY); }
    double aZ(double _aZ) { return acceleration_.z(_aZ); }

    void tick() {
      // Increment position using Euler method.
      position_ += .5 * velocity_;
      velocity_ += acceleration_;
      position_ += .5 * velocity_;
    }

    private:
    math::Point3d position_;
    math::Normal3d velocity_, acceleration_;
  };
}
