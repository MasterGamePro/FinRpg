#pragma once

namespace fin::data {
  template <typename T>
  class IStack {
    public:
    virtual ~IStack() {}

    virtual void push(const T& t) = 0;
    virtual bool pop() = 0;
    virtual T& peek() = 0;

    virtual void clear() = 0;
    virtual int size() const = 0;
    bool is_empty() const { return size() == 0; }
  };
}
