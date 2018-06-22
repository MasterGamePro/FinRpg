#pragma once
#include "fin/math/geometry/point3d.h"
#include "fin/math/geometry/normal3d.h";

namespace fin::app {
  class PositionData3d {
    public:
    double p_x() const { return position_.x(); }
    double p_y() const { return position_.y(); }
    double p_z() const { return position_.z(); }
    double p_x(double x) { return position_.x(x); }
    double p_y(double y) { return position_.y(y); }
    double p_z(double z) { return position_.z(z); }
    const math::Point3d& p_xyz() const { return position_; }

    double v_x() const { return velocity_.x(); }
    double v_y() const { return velocity_.y(); }
    double v_z() const { return velocity_.z(); }
    double v_x(const double _vX) { return velocity_.x(_vX); }
    double v_y(const double _vY) { return velocity_.y(_vY); }
    double v_z(const double _vZ) { return velocity_.z(_vZ); }
    const math::Normal3d& v_xyz() const { return velocity_; }

    double a_x() const { return acceleration_.x(); }
    double a_y() const { return acceleration_.y(); }
    double a_z() const { return acceleration_.z(); }
    double a_x(double _aX) { return acceleration_.x(_aX); }
    double a_y(double _aY) { return acceleration_.y(_aY); }
    double a_z(double _aZ) { return acceleration_.z(_aZ); }
    const math::Normal3d& a_xyz() const { return acceleration_; }

    void tick() {
      // TODO: Increment position using Euler method.
      position_ += velocity_;
      velocity_ += acceleration_;
    }

    private:
    math::Point3d position_;
    math::Normal3d velocity_, acceleration_;
  };
}
