#pragma once

#include "fin/audio/ibuffer.h"

#include <AL/al.h>

namespace fin::audio {
  class BufferAl : public IBuffer {
    public:
    BufferAl() { alGenBuffers(1, &buffer_); }
    ~BufferAl() { alDeleteBuffers(1, &buffer_); }

    private:
    ALuint buffer_;
  };
}
