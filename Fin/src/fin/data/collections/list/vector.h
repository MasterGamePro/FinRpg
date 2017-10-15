#pragma once

#include <vector>
#include "ilist.h"

namespace fin::data {
  template <typename T>
  class Vector : public IList<T> {
    public:

    virtual ~Vector() { clear(); }

    T& at( int index ) override final { return list.at( index ); }
    T& front() override final { return list.front(); }
    T& back() override final {
      if ( size() > 0 ) {
        return list.back();
      }

      throw std::exception( "Vector.back: List is empty." );
    }

    void insertBefore( int index, const T& t ) override final { list.insert( list.begin() + index, t ); }
    void insertAfter( int index, const T& t ) override final { list.insert( list.begin() + index + 1, t ); }
    void removeAt( int index ) override final { list.erase( list.begin() + index ); }

    void pushBack( const T& t ) override final { list.push_back( t ); }
    bool popBack() override final {
      auto count = size();
      list.pop_back();
      return ( count >= 1 );
    }

    void clear() override final { list.clear(); }
    int size() override final { return list.size(); }

    void iterate( const std::function< void( T t, int i ) >& lambda ) override final {
      int i = 0;
      for ( auto it = list.cbegin(), end = list.cend(); it != end; ++it, i++ ) {
        lambda( *it, i );
      }
    }

    private:
    std::vector<T> list;
  };
}