#pragma once

namespace fin::math {
  class IRectangle {
    public:
    virtual ~IRectangle() {}

    virtual double get_x() const = 0;
    virtual double get_y() const = 0;
    virtual double get_width() const = 0;
    virtual double get_height() const = 0;

    virtual double set_x(double x) = 0;
    virtual double set_y(double y) = 0;
    virtual double set_width(double width) = 0;
    virtual double set_height(double height) = 0;

    virtual void set_position(double x, double y) {
      set_x(x);
      set_y(y);
    }

    virtual void set_size(double width, double height) {
      set_width(width);
      set_height(height);
    }

    virtual void set_bounds(double x, double y, double width, double height) {
      set_position(x, y);
      set_size(width, height);
    }

    double get_area() { return get_width() * get_height(); };
  };
}