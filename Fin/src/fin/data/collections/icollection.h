#pragma once

#include "../iiterable.h"

namespace fin::data {
  template <typename T>
  class ICollection : public IIterable<T> {
    public:
    virtual ~ICollection() {}

    virtual void clear() = 0;
    virtual int size() const = 0;
    bool is_empty() const { return size() == 0; }

    virtual bool contains(const T& t) const = 0;
  };
}