#pragma once

namespace fin::data {
  template <typename T>
  class IStack {
    public:
    virtual void push( const T& t ) = 0;
    virtual bool pop() = 0;
    virtual T& peek() = 0;

    virtual void clear() = 0;
    virtual int size() = 0;
    bool is_empty() { return size() == 0; }
  };
}
