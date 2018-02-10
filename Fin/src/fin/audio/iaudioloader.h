#pragma once
#include "fin/io/file.h"
#include "ibuffer.h"

namespace fin::audio {
  class IAudioLoader {
    public:
    virtual ~IAudioLoader() {}

    IBuffer* load(io::File* file) {

    }
  };
}
