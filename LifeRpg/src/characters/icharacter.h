#pragma once
#include <stdio.h>
#include <direct.h>
#include "fin/algorithm/string/format.h"
#include "fin/app/actor/iactor.h"
#include "fin/debug/memory.h"
#include "fin/graphics/texture/imagetexture.h"
#include "fin/input/iinput.h"
#include "fin/math/trig.h"
#include "fin/time/deltatime.h"

class ICharacter : public fin::app::IActor {
  public:
  ICharacter( std::string name, fin::graphics::ITextures* ts ) {
    ADD_TO_TOTAL_MEMORY_CHILD( ICharacter, fin::app::IActor );

    char buffer[FILENAME_MAX];
    _getcwd( buffer, FILENAME_MAX );

    std::string folderPath = "resources/characters/" + name + "/";
    standingTextures.push_back( ts->load_texture( fin::io::File( folderPath + "standing-0.png" ) ) );

    for ( int i = 0; i < 4; i++ ) {
      std::string path = fin::algorithm::string_format( "%swalking-%d.png", folderPath.c_str(), i );
      fin::debug::Log::println( path );
      walkingTextures.push_back( ts->load_texture( fin::io::File( path ) ) );
    }

    shadowTexture = ts->load_texture( fin::io::File( "resources/images/shadow.png" ) );
  }

  ~ICharacter() {
    REMOVE_FROM_TOTAL_MEMORY_CHILD( ICharacter, fin::app::IActor );
  }

  protected:
  void move( double amount, double dir ) {
    if ( amount > 0 ) {
      this->dir = dir;
      isMoving = true;
      x += fin::math::Trig::cosd( dir ) * amount;
      y += fin::math::Trig::sind( dir ) * amount;
    }
    else {
      isMoving = false;
    }
  }

  void on_tick_physics() override final {

  }

  void on_tick_collision() override final {

  }

  void on_tick_animation() override {
    // TODO: Rotate based on the trajectory of the angular velocity.
    double camDirection = -90;

    double angleError = 20;
    double angleDiff = fin::math::Trig::angle_diffd( camDirection, dir );

    double absAngleDiff = fabs( angleDiff );
    if ( absAngleDiff > angleError && absAngleDiff < 180 - angleError ) {
      targetFlipDirection = 90 + ( angleDiff > 0 ? 1 : -1 ) * 90;
    }

    double flipSpeed = fin::time::DeltaTime::adjust_velocity( 20 );
    double angleDist = fin::math::Trig::angle_distd( flipDirection, targetFlipDirection );

    if ( fabs( angleDist ) <= flipSpeed ) {
      flipDirection = targetFlipDirection;
    }
    else {
      flipDirection += ( angleDist > 0 ? 1 : -1 ) * flipSpeed;
    }
  }

  void on_tick_audio() override final {

  }

  void on_tick_render_ortho( fin::graphics::IGraphics* g ) override {}

  void on_tick_render_perspective( fin::graphics::IGraphics* g ) override final {
    g->r3d()->draw_floor( -500, -500, 500, 500, -1 );

    fin::graphics::ITransform* t = g->t();
    t->identity();
    t->translate( x, y, z );
    t->rotate_z( flipDirection );

    g->p()->color3d( 1, 1, 1 );

    g->ts()->bind( shadowTexture );
    g->r3d()->draw_floor( -5, -5, 5, 5, 0 );

    fin::graphics::ImageTexture* img;

    if ( isMoving ) {
      index += .15;
      img = walkingTextures[( int ) index % 4];
    }
    else {
      img = standingTextures[0];
    }

    int xd = -2;

    g->ts()->bind( img );
    g->r3d()->draw_wall( xd - 8, 0, 16, xd + 8, 0, 0 );
    g->ts()->bind( nullptr );
  }

  protected:
  bool isMoving = false;
  double x = 0, y = 0, z = 0, s = 16;
  double vX = 0, vY = 0;
  double dir = 0;
  double index = 0;

  private:
  double flipDirection = 0, targetFlipDirection = 0;
  fin::data::StlVector<fin::graphics::ImageTexture*> standingTextures;
  fin::data::StlVector<fin::graphics::ImageTexture*> walkingTextures;
  fin::graphics::ImageTexture* shadowTexture;
};
