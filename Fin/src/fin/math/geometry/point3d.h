#pragma once

namespace fin::math {
  class Normal3d;

  class Point3d {
    public:
    Point3d() {
      x( 0 );
      y( 0 );
      z( 0 );
    }
    Point3d( const double x, const double y, const double z ) {
      this->x( x );
      this->y( y );
      this->z( z );
    }

    Point3d& set( const Point3d& other ) {
      x( other.x() );
      y( other.y() );
      z( other.z() );
      return *this;
    }
    Point3d& add( const Normal3d& other ) {}

    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }

    double x( const double x ) { return this->x_ = x; }
    double y( const double y ) { return this->y_ = y; }
    double z( const double z ) { return this->z_ = z; }

    Point3d& operator=( const Point3d& other ) { return set( other ); }

    Normal3d operator-( const Point3d& other ) const;
    Point3d operator+( const Normal3d& other ) const;
    /*Point3d& operator+= ( const Normal3d& other ) const {
      Point3d point = this + other;
      return *this;
    }*/

    private:
    double x_, y_, z_;
  };
}