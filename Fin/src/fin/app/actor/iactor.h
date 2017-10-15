#pragma once
#include "fin/data/collections/set/hashset.h"
#include "fin/graphics/igraphics.h"
#include "fin/input/iinput.h"
#include "fin/app/iapp.h"

/*
 * glMatrixMode( GL_MODELVIEW );
 * glLoadIdentity();
 */

namespace fin::app {
  class IActor {
    public:
    static void tick_all( IApp* a ) {
      input::IInput* input = a->get_input();
      toplevelInstances.iterate( [input] ( IActor* actor, int i ) { actor->tick_control( input ); } );
      toplevelInstances.iterate( [input] ( IActor* actor, int i ) { actor->tick_physics(); } );
      toplevelInstances.iterate( [input] ( IActor* actor, int i ) { actor->tick_collision(); } );
      toplevelInstances.iterate( [input] ( IActor* actor, int i ) { actor->tick_animation(); } );
      toplevelInstances.iterate( [input] ( IActor* actor, int i ) { actor->tick_audio(); } );
    }

    IActor() {
      toplevelInstances.add( this );
    }
    virtual ~IActor() {}

    void add_child( IActor* child ) {
      if ( toplevelInstances.remove( child ) ) {
        children.add( child );
      }
    }

    void tick_control( input::IInput* input ) {
      on_tick_control( input );
      children.iterate( [input] ( IActor* child, int i ) {
        child->tick_control( input );
      } );
    }
    void tick_physics() {
      on_tick_physics();
      children.iterate( [] ( IActor* child, int i ) {
        child->tick_physics();
      } );
    }
    void tick_collision() {
      on_tick_collision();
      children.iterate( [] ( IActor* child, int i ) {
        child->tick_collision();
      } );
    }
    void tick_animation() {
      on_tick_animation();
      children.iterate( [] ( IActor* child, int i ) {
        child->tick_animation();
      } );
    }
    void tick_audio() {
      on_tick_audio();
      children.iterate( [] ( IActor* child, int i ) {
        child->tick_audio();
      } );
    }
    void tick_render( graphics::IGraphics* g ) {
      graphics::ITransform* t = g->t();

      t->set_target_matrix( graphics::MATRIX_MODELVIEW );
      t->push_matrix();

      on_tick_render( g );

      children.iterate( [g] ( IActor* child, int i ) {
        child->tick_render( g );
      } );

      t->pop_matrix();
    }

    protected:
    virtual void on_tick_control( input::IInput* input ) = 0;
    virtual void on_tick_physics() = 0;
    virtual void on_tick_collision() = 0;
    virtual void on_tick_animation() = 0;
    virtual void on_tick_audio() = 0;
    virtual void on_tick_render( graphics::IGraphics* graphics ) = 0;

    private:
    static data::HashSet<IActor*> toplevelInstances;
    data::HashSet<IActor*> children;
  };
}
