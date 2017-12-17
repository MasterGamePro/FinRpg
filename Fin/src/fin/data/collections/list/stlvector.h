#pragma once

#include <vector>
#include "ilist.h"
#include "fin/debug/exception.h"

namespace fin::data {
  template <typename T>
  class StlVector : public IList<T> {
    public:

    virtual ~StlVector() { clear(); }

    T& at( int index ) override final { return list.at( index ); }
    T& front() override final {
      if ( size() > 0 ) {
        return list.front();
      }

      throw debug::Exception( "StlVector", "front", "The list is empty." );
    }
    T& back() override final {
      if ( size() > 0 ) {
        return list.back();
      }

      throw debug::Exception("StlVector", "back", "The list is empty.");
    }

    void insert_before( int index, const T& t ) override final { list.insert( list.begin() + index, t ); }
    void insert_after( int index, const T& t ) override final { list.insert( list.begin() + index + 1, t ); }
    void remove_at( int index ) override final { list.erase( list.begin() + index ); }

    void push_back( const T& t ) override final { list.push_back( t ); }
    bool pop_back() override final {
      auto si = size();
      if ( si > 0 ) {
        list.pop_back();
        return true;
      }
      return false;
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