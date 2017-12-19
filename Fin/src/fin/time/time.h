#pragma once
#include <chrono>
#include <thread>

namespace fin::time {
  class Time {
    public:

    // TODO: Cache each frame, so successive calls aren't slow.
    static std::chrono::milliseconds get_epoch_ms() { return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ); }

    static double mod_ms( double millisecsN ) {
      return fmod( get_epoch_ms().count(), millisecsN ) / millisecsN;
    }

    static void sleep_ms( long long ms ) { std::this_thread::sleep_for( std::chrono::milliseconds( ms ) ); }

    private:
    Time() {}
  };
}
