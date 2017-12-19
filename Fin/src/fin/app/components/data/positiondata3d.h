#pragma once
#include "fin/math/geometry/point3d.h"
#include "fin/math/geometry/normal3d.h";

namespace fin::app {
  class PositionData3d {
    public:
    double x() const { return position.x(); }
    double y() const { return position.y(); }
    double z() const { return position.z(); }
    double x( double _x ) { return position.x( _x ); }
    double y( double _y ) { return position.y( _y ); }
    double z( double _z ) { return position.z( _z ); }

    double vX() const { return _vX; }
    double vY() const { return _vY; }
    double vX( double _vX ) { return this->_vX = _vX; }
    double vY( double _vY ) { return this->_vY = _vY; }

    double aX() const { return _aX; }
    double aY() const { return _aY; }
    double aX( double _aX ) { return this->_aX = _aX; }
    double aY( double _aY ) { return this->_aY = _aY; }

    void tick() {
      position += velocity;
      velocity += acceleration;
    }

    private:
    math::Point3d position;
    math::Normal3d velocity, acceleration;
  };
}