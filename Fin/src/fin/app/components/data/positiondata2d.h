#pragma once

class PositionData2d {
  public:
  double x() const { return _x; }
  double y() const { return _y; }
  double x( double _x ) { return this->_x = _x; }
  double y( double _y ) { return this->_y = _y; }

  double vX() const { return _vX; }
  double vY() const { return _vY; }
  double vX( double _vX ) { return this->_vX = _vX; }
  double vY( double _vY ) { return this->_vY = _vY; }

  double aX() const { return _aX; }
  double aY() const { return _aY; }
  double aX( double _aX ) { return this->_aX = _aX; }
  double aY( double _aY ) { return this->_aY = _aY; }

  private:
  double _x, _y, _vX, _vY, _aX, _aY, _w, _h;
};