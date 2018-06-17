#pragma once

#include "inormal3d.h"

namespace fin::math {
  class Normal3d : public INormal3d {
    public:
    static Normal3d UP;

    Normal3d() {
      x( 0 );
      y( 0 );
      z( 0 );
    }

    Normal3d( double x_, double y_, double z_ ) {
      x( x_ );
      y( y_ );
      z( z_ );
    }

    double x() const override final { return x_; }
    double y() const override final { return y_; }
    double z() const override final { return z_; }

    double x( double x_ ) { return this->x_ = x_; }
    double y( double y_ ) { return this->y_ = y_; }
    double z( double z_ ) { return this->z_ = z_; }

    Normal3d& Normal3d::operator+=(const Normal3d& other);

    private:
    double x_, y_, z_;;
  };
}