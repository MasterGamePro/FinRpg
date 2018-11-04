#pragma once
#include <functional>
#include "promise-cpp/promise.h"

namespace fin::event {
  class Event {
    public:
    void fire() {

    }

    void thenOnce(std::function<void()> handler) const {
      // TODO: Allow chaining. Maybe not promise?
    }

    void thenAlways(std::function<void()> handler) const {
      handler.
    }

    private:
    std::vector<std::function<void()>> onceList;
    std::vector<std::function<void()>> alwaysList;
  };
}
