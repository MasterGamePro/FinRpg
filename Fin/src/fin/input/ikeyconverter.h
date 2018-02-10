#pragma once

#include "keydefs.h"

namespace fin::input {
  class IKeyConverter {
    public:
    virtual ~IKeyConverter() {}

    virtual Keycode get_keycode( int library_code ) = 0;
    virtual int get_tkeycode( Keycode code ) = 0;
  };
}
