#pragma once

namespace fin::audio {
  class ISingleSource {
    public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
  };
}