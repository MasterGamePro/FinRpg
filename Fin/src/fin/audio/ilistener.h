#pragma once

namespace fin::audio {
  class IListener {
    public:
    virtual void set_position( const double x, const double y, const double z ) = 0;
    virtual void set_velocity( const double x, const double y, const double z ) = 0;
    virtual void set_orientation( const double nx, const double ny, const double nz, const double upX, const double upY, const double upZ ) = 0;
  };
}