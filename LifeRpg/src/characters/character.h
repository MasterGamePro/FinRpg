#pragma once
#include "fin/input/iinput.h"
#include "fin/app/actor/iactor.h"
#include "fin/math/trig.h"

class Character : public fin::app::IActor {
  protected:
  void on_tick_control( fin::input::IInput* i ) override final {
    const auto il = i->getInputLayout();

    const auto pdi = il->getPrimaryDirectionalInput();
    const auto amt = pdi->getHeldAmount();

    if ( amt > 0 ) {
      dir = pdi->getHeldDirection();
    }

    x += fin::math::Trig::cosd( dir ) * amt;
    y += fin::math::Trig::sind( dir ) * amt;
  }

  void on_tick_physics() override final {

  }

  void on_tick_collision() override final {

  }

  void on_tick_animation() override final {
    flipDirection = 0;
  }

  void on_tick_audio() override final {

  }

  void on_tick_render( fin::graphics::IGraphics* g ) override final {
    g->p()->color3d( 1, 1, 1 );

    g->rt()->draw_string( "The quick, brown fox jumps over the lazy dog.", 0, 0 );

    fin::graphics::ITransform* t = g->t();

    t->translate( x, y );
    t->rotate_y( flipDirection ); //_z

    g->r2d()->fillRectangle( -s, -2 * s, 2 * s, 2 * s );
    g->p()->color3d( 1, 0, 0 );
    g->r2d()->fillRectangle( .8 * s, -2 * s, .2 * s, 2 * s );

    t->scale( 1, .2 );
    g->p()->color3d( .3, .3, .3 );
    g->r2d()->fillCircle( 0, 0, s );
  }

  private:
  double x = 32, y = 32, s = 16;
  double vX = 0, vY = 0;
  double dir = 0;
  double flipDirection, targetFlipDirection;
};
