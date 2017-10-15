#pragma once

#include "../icollection.h"

namespace fin::data {
  template <typename T>
  class ISet : public ICollection<T> {
    public:

    virtual ~ISet() {}

    virtual bool add( const T& t ) = 0;
    virtual bool remove( const T&t ) = 0;
  };
}