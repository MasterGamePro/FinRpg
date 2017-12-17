#pragma once
#include "istack.h"
#include <stack>

namespace fin::data {
  template <typename T>
  class StlStack : public IStack<T> {
    public:
    virtual void push( const T& t ) { stack.push( t ); }
    bool pop() override final {
      if ( size() > 0 ) {
        stack.pop();
        return true;
      }
      return false;
    }
    T& peek() override final {
      if ( !is_empty() ) {
        return stack.top();
      }
      throw debug::Exception( "StlStack", "peek", "The stack is empty." );
    }

    void clear() override final { while ( pop() ); }
    int size() override final { return stack.size(); }

    private:
    std::stack<T> stack;
  };
}
