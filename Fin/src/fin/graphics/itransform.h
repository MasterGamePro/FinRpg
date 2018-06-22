#pragma once

#include "fin/math/geometry/inormal3d.h"
#include "fin/math/geometry/point3d.h"

namespace fin::graphics {
  enum class MatrixType {
    PROJECTION,
    MODELVIEW
  };

  class ITransform {
    public:
    virtual ~ITransform() {}

    virtual void set_target_matrix(MatrixType matrixType) = 0;

    virtual void push_matrix() = 0;
    virtual void pop_matrix() = 0;

    virtual void identity() = 0;

    virtual void translate(const double x, const double y) = 0;
    virtual void translate(const double x, const double y, const double z) = 0;
    void translate(const math::Point3d& point) {
      translate(point.x(), point.y(), point.z());
    }

    virtual void scale(const double x, const double y) = 0;
    virtual void scale(const double x, const double y, const double z) = 0;

    virtual void rotate_x(const double deg) = 0;
    virtual void rotate_y(const double deg) = 0;
    virtual void rotate_z(const double deg) = 0;
    virtual void rotate_around_axis(const math::INormal3d& axis,
                                    const double deg) = 0;

    virtual void perspective(double fov, double aspect, double nearValue,
                             double farValue) = 0;
    virtual void ortho(double left, double right, double bottom, double top,
                       double near, double far) = 0;
    virtual void look_at(const math::Point3d& from, const math::Point3d& to,
                         const math::INormal3d& up) = 0;
  };
}
