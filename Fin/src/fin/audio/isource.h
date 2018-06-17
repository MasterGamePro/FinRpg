#pragma once

namespace fin::audio {
  class ISource {
    public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    virtual void set_pitch( const double pitch ) = 0;
    virtual void set_gain( const double gain ) = 0;
    virtual void set_position( const double x, const double y, const double z ) = 0;
    virtual void set_velocity( const double x, const double y, const double z ) = 0;

    virtual void toggle_repeat( const bool doRepeat ) = 0;
  };
}