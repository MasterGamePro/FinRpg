#pragma once

#include <AL/al.h>

#include "fin/audio/isource.h"

namespace fin::audio {
  class SourceAl : public ISource {
    public:
    SourceAl() { alGenSources(1, &source_); }
    ~SourceAl() { alDeleteSources(1, &source_); }

    void play() override final { alSourcePlay(source_); }
    void pause() override final { alSourcePause(source_); }
    void stop() override final { alSourceStop(source_); }

    void set_pitch(const double pitch) override final {
      alSourcef(source_, AL_PITCH, pitch);
    }
    void set_gain(const double gain) override final {
      alSourcef(source_, AL_GAIN, gain);
    }

    void set_position(const double x, const double y, const double z) override
    final { alSource3f(source_, AL_POSITION, x, y, z); }

    void set_velocity(const double x, const double y, const double z) override
    final { alSource3f(source_, AL_VELOCITY, x, y, z); }

    void toggle_repeat(const bool doRepeat) override final {
      alSourcei(source_, AL_LOOPING, doRepeat ? AL_TRUE : AL_FALSE);
    }

    private:
    ALuint source_;
  };
}
