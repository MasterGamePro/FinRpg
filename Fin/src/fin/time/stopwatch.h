#pragma once

#include "fin/time/Time.h"

namespace fin::time {
  class Stopwatch {
    public:
    Stopwatch() { reset(); }

    void start() {
      if (!isActive_) {
        isActive_ = true;
        startMs_ = Time::get_epoch_ms();
      }
    }
    void stop() {
      if (isActive_) {
        isActive_ = false;
        progressMs_ += Time::get_epoch_ms() - startMs_;
      }
    }
    void reset() {
      progressMs_ = std::chrono::milliseconds::zero();
      isActive_ = false;
    }

    long long get_current_ms() const {
      auto total = progressMs_;
      if (isActive_) {
        total += Time::get_epoch_ms() - startMs_;
      }
      return total.count();
    }

    private:
    std::chrono::milliseconds progressMs_, startMs_;
    bool isActive_;
  };
}
