#pragma once

namespace fin::math {
  class Point2d {
  public:
    double x() const { return x_; }
    double y() const { return y_; }
    double x(double x_) { return this->x_ = x_; }
    double y(double y_) { return this->y_ = y_; }

  private:
    double x_, y_;
  };
}