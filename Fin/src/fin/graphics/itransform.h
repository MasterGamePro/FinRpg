#pragma once

namespace fin::graphics {
  enum MatrixType {
    MATRIX_PROJECTION,
    MATRIX_MODELVIEW
  };

  class ITransform {
    public:
    virtual void set_target_matrix( MatrixType matrixType ) = 0;

    virtual void ortho( double left, double right, double bottom, double top, double near, double far ) = 0;

    virtual void push_matrix() = 0;
    virtual void pop_matrix() = 0;

    virtual void identity() = 0;

    virtual void translate( double x, double y ) = 0;
    virtual void translate( double x, double y, double z ) = 0;

    virtual void scale( double x, double y ) = 0;
    virtual void scale( double x, double y, double z ) = 0;

    virtual void rotate_x( double deg ) = 0;
    virtual void rotate_y( double deg ) = 0;
    virtual void rotate_z( double deg ) = 0;
  };
}