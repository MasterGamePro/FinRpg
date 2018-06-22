#pragma once

#include "stopwatch.h"

namespace fin::time {
  class CountdownTimer {
    public:
    bool is_done() const {
      const auto currentMs = stopwatch_.get_current_ms();
      return currentMs >= durationMs_;
    }

    void start() { stopwatch_.start(); }
    void stop() { stopwatch_.stop(); }

    void reset() { stopwatch_.reset(); }

    void set_duration_ms(long long durationMs) { durationMs_ = durationMs; }

    private:
    Stopwatch stopwatch_;
    long long progressMs_, durationMs_;
  };
}
