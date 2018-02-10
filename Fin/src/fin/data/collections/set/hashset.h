#pragma once

#include <unordered_set>
#include "iset.h"

namespace fin::data {
  template <typename T>
  class HashSet : public ISet<T> {
    public:

    virtual ~HashSet() { clear(); }

    bool contains( const T& t ) const override final {
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
    int size() const override final { return set.size(); }

    void iterate( const std::function< void( T& t, int i ) >& lambda ) override final {
      auto i = 0;
      for ( auto t : set ) {
        lambda( t, i++ );
      }
    }

    void const_iterate(const std::function< void(const T& t, int i) >& lambda) const override final {
      auto i = 0;
      for (const auto t : set) {
        lambda(t, i++);
      }
    }

    private:

    std::unordered_set<T> set;
  };
}