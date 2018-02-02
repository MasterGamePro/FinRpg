#pragma once

#include <AL/alc.h>
#include "../../iaudio.h"
#include <exception>

namespace fin::audio {
  class AudioAl : public IAudio {
    public:
    AudioAl() {}

    void init() override final {
      device = alcOpenDevice( nullptr );
      if ( !device ) {
        throw std::exception( "Failed to open default audio device for OpenAL.\n" );
      }
      context = alcCreateContext( device, nullptr );
      if ( !alcMakeContextCurrent( context ) ) {
        throw std::exception( "Failed to make context current.\n" );
      }
    }
    void deinit() override final {
      alcDestroyContext( context );
      alcCloseDevice( device );
    }

    private:
    ALCdevice * device;
    ALCcontext *context;
  };
}
