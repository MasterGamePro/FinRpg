#pragma once

#include "fin/app/iservice.h"
#include "ilistener.h"

namespace fin::audio {
  class IAudio : public app::IService {
    public:
    virtual ~IAudio() {}

    virtual IListener* get_listener() = 0;
  };
}