#pragma once

namespace fin::app {
  class IService {
    public:
    virtual void init() = 0;
    virtual void deinit() = 0;
  };
}