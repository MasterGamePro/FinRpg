#pragma once
#include <AL/al.h>
#include "fin/audio/isource.h"

namespace fin::audio {
  class SourceAl : public ISource {
    public:
    SourceAl() {
      alGenSources( 1, &source );
    }

    void set_pitch( const double pitch ) override final {
      alSourcef( source, AL_PITCH, pitch );
    }
    void set_gain( const double gain ) override final {
      alSourcef( source, AL_GAIN, gain );
    }
    void set_position( const double x, const double y, const double z ) override final {
      alSource3f( source, AL_POSITION, x, y, z );
    }
    void set_velocity( const double x, const double y, const double z ) override final {
      alSource3f( source, AL_VELOCITY, x, y, z );
    }
    void toggle_repeat( const bool doRepeat ) override final {
      alSourcei( source, AL_LOOPING, AL_FALSE );
    }

    private:
    ALuint source;
  };
}
