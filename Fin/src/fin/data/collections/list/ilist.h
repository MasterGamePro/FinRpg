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
    T& random() { return at( generate_random_index() ); }

    int find_index_of( const T& t ) {
      for ( int i = 0, si = this->size(); i < si; i++ ) {
        if ( this->at( i ) == t ) {
          return i;
        }
      }

      return -1;
    }
    bool contains( const T& t ) override final { return find_index_of( t ) != -1; }

    virtual void insert_before( int index, const T& t ) = 0;
    virtual void insert_after( int index, const T& t ) = 0;
    virtual void remove_at( int index ) = 0;
    void remove_random() { remove( generate_random_index() ); }
    bool remove( const T& t ) {
      int i = find_index_of( t );
      if ( i != -1 ) {
        remove_at( i );
        return true;
      }
      return false;
    }

    virtual void push_front( const T& t ) { insert_before( 0, t ); }
    virtual void push_back( const T& t ) { insert_after( this->size() - 1, t ); }
    virtual bool pop_front() {
      if ( this->size() > 0 ) {
        remove_at( 0 );
        return true;
      }
      return false;
    }
    virtual bool pop_back() {
      int si = this->size();
      if ( si > 0 ) {
        remove_at( si - 1 );
        return true;
      }
      return false;
    }

    T& operator[]( int index ) { return at( index ); }

    private:
    int generate_random_index() { return math::Random::randomi( 0, this->size() ); }
  };
}