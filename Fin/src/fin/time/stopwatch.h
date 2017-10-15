#pragma once

#include "fin/time/Time.h"

namespace fin::time {
  class Stopwatch {
    public:
    Stopwatch() {
      reset();
    }

    void reset() { startMs = Time::get_epoch_ms(); }
    long long get_current_ms() const { return (Time::get_epoch_ms() - startMs).count(); }

    private:
    std::chrono::milliseconds startMs;
  };
}