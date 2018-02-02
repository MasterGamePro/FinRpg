#pragma once
#include <AL/al.h>
#include "fin/audio/ilistener.h"

namespace fin::audio {
  class ListenerAl : public IListener {
    public:
    void set_position( const double x, const double y, const double z ) override final {
      alListener3f( AL_POSITION, x, y, z );
    }
    void set_velocity( const double x, const double y, const double z ) override final {
      alListener3f( AL_VELOCITY, x, y, z );
    }
    void set_orientation( const double nx, const double ny, const double nz, const double upX, const double upY, const double upZ ) override final {
      ALfloat values[6] = { nx, ny, nz, upX, upY, upZ };
      alListenerfv( AL_ORIENTATION, values );
    }
  };
}
