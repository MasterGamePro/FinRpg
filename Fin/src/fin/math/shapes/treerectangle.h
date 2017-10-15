#pragma once
#include "irectangle.h"
#include "fin/data/collections/set/hashset.h"
#include <algorithm>

namespace fin::math {
  class TreeRectangle : public IRectangle {
    public:
    double get_clipped_x() const { return clip_x; }
    double get_clipped_y() const { return clip_y; }
    double get_clipped_width() const { return clip_width; }
    double get_clipped_height() const { return clip_height; }

    double get_absolute_x() const { return absolute_x; }
    double get_absolute_y() const { return absolute_y; }

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_width() const { return width; }
    double get_height() const { return height; }

    double set_x( double x ) {
      this->x = x;
      update_clip();
      return x;
    }
    double set_y( double y ) {
      this->y = y;
      update_clip();
      return y;
    }
    double set_width( double width ) {
      this->width = width;
      update_clip();
      return width;
    }
    double set_height( double height ) {
      this->height = height;
      update_clip();
      return height;
    }

    void set_position( double x, double y ) final override {
      this->x = x;
      this->y = y;
      update_clip();
    }

    void set_size( double width, double height ) final override {
      this->width = width;
      this->height = height;
      update_clip();
    }

    void set_bounds( double x, double y, double width, double height ) final override {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      update_clip();
    }

    void add_child( TreeRectangle* child ) {
      if ( child == nullptr ) {
        throw std::exception( "TreeRectangle.add_child: Null child." );
      }

      child->attach_to( this );
    }

    void remove_child( TreeRectangle* child ) {
      if ( children.contains( child ) ) {
        child->detach();
      }
    }

    void attach_to( TreeRectangle* parent ) {
      if ( parent == nullptr ) {
        throw std::exception( "TreeRectangle.attach_to: Null parent." );
      }

      if ( parent != this->parent ) {
        if ( this->parent != nullptr ) {
          this->parent->children.remove( this );
        }

        this->parent = parent;
        parent->children.add( this );

        update_clip();
      }
    }

    void detach() {
      if ( this->parent != nullptr ) {
        this->parent->children.remove( this );
        this->parent = nullptr;
        update_clip();
      }
    }

    private:
    void update_clip() {
      double parentX = 0, parentY = 0,
        parentWidth = DBL_MAX, parentHeight = DBL_MAX;

      if ( parent != nullptr ) {
        parentX = parent->get_absolute_x();
        parentY = parent->get_absolute_y();
        parentWidth = parent->get_clipped_width();
        parentHeight = parent->get_clipped_height();
      }

      clip_x = std::max( 0., x );
      clip_y = std::max( 0., y );
      absolute_x = parentX + x;
      absolute_y = parentY + y;
      clip_width = std::max( 0., std::min( width, parentWidth - clip_x ) );
      clip_height = std::max( 0., std::min( height, parentHeight - clip_y ) );

      children.iterate( [] ( TreeRectangle* child, int i ) {
        child->update_clip();
      } );
    }

    TreeRectangle* parent;
    data::HashSet<TreeRectangle*> children;

    double x, y, width, height;
    double absolute_x, absolute_y;
    double clip_x, clip_y, clip_width, clip_height;
  };
}
