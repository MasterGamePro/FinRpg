#pragma once

#include <unordered_set>
#include "iset.h"

namespace fin::data {
  template <typename T>
  class HashSet : public ISet<T> {
    public:

    virtual ~HashSet() { clear(); }

    bool contains( const T& t ) override final {
      return set.find( t ) != set.end();
    }
    bool add( const T& t ) override final {
      int si = size();
      set.insert( t );
      return ( size() != si );
    }
    bool remove( const T&t ) override final {
      int si = size();
      set.erase( set.find( t ) );
      return ( size() != si );
    };

    void clear() override final { set.clear(); }
    int size() override final { return set.size(); }

    void iterate( const std::function< void( T t, int i ) >& lambda ) override final {
      int i = 0;
      for ( auto it = set.cbegin(), end = set.cend(); it != end; ++it, i++ ) {
        lambda( *it, i );
      }
    }

    private:

    std::unordered_set<T> set;
  };
}