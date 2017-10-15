#pragma once

#include "../icollection.h"

namespace fin::data {
  template <typename T>
  class IList : public ICollection<T> {
    public:

    virtual ~IList() {}

    virtual T& at( int index ) = 0;
    virtual T& front() { return at( 0 ); }
    virtual T& back() { return at( this->size() - 1 ); }

    int indexOf( const T& t ) {
      for ( int i = 0, si = this->size(); i < si; i++ ) {
        if ( this->at( i ) == t ) {
          return i;
        }
      }

      return -1;
    }
    bool contains( const T& t ) override final { return indexOf( t ) != -1; }

    virtual void insertBefore( int index, const T& t ) = 0;
    virtual void insertAfter( int index, const T& t ) = 0;
    virtual void removeAt( int index ) = 0;
    bool remove( const T& t ) {
      int i = indexOf( t );
      if ( i != -1 ) {
        removeAt( i );
        return true;
      }
      return false;
    }

    virtual void pushFront( const T& t ) { insertBefore( 0, t ); }
    virtual void pushBack( const T& t ) { insertAfter( this->size() - 1, t ); }
    virtual bool popFront() {
      if ( this->size() > 0 ) {
        removeAt( 0 );
        return true;
      }
      return false;
    }
    virtual bool popBack() {
      int si = this->size();
      if ( si > 0 ) {
        removeAt( si - 1 );
        return true;
      }
      return false;
    }

    T& operator[]( int index ) { return at( index ); }
  };
}