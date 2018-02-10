#pragma once

#include <functional>

namespace fin::data {
  template <typename T>
  class IIterable {
    public:
    virtual ~IIterable() {}

    virtual void iterate(const std::function< void(T& t, int i) >& lambda) = 0;
    virtual void const_iterate(const std::function< void(const T& t, int i) >& lambda) const = 0;
  };
}