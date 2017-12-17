#pragma once
#include "fin/input/iinput.h"
#include "fin/app/actor/iactor.h"
#include "fin/math/trig.h"
#include "time/deltatime.h"
#include "graphics/texture/imagetexture.h"
#include "fin/debug/memory.h"

class ICharacter : public fin::app::IActor {
public:
  ICharacter() {
    fin::debug::totalBytes -= sizeof(fin::app::IActor);
    fin::debug::totalBytes += sizeof(ICharacter);
  }

  ~ICharacter() {
    fin::debug::totalBytes -= sizeof(ICharacter);
  }

protected:
  void on_tick_physics() override final {

  }

  void on_tick_collision() override final {

  }

  void on_tick_animation() override {
    double camDirection = 90;

    double angleError = 20;
    double angleDiff = fin::math::Trig::angle_diff(camDirection, dir);
    double absAngleDiff = fabs(angleDiff);
    if (absAngleDiff > angleError && absAngleDiff < 180 - angleError) {
      targetFlipDirection = 90 - (angleDiff > 0 ? 1 : -1) * 90;
    }

    double flipSpeed = fin::time::DeltaTime::adjust_velocity(20);
    double angleDist = fin::math::Trig::angle_dist(flipDirection, targetFlipDirection);

    if (fabs(angleDist) <= flipSpeed) {
      flipDirection = targetFlipDirection;
    }
    else {
      flipDirection += (angleDist > 0 ? 1 : -1) * flipSpeed;
    }
  }

  void on_tick_audio() override final {

  }

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override {}

  void on_tick_render_perspective(fin::graphics::IGraphics* g) override final {
    fin::graphics::ITransform* t = g->t();
    t->identity();
    t->translate(x, y, z);
    t->rotate_z(flipDirection);

    fin::debug::Log::println("%lf", flipDirection);

    g->p()->color3d(1, 1, 1);
    g->r3d()->draw_floor(-8, -8, 8, 8, 0);
    g->r3d()->draw_wall(-8, 0, 16, 8, 0, 0);
  }

protected:
  double x = 0, y = 0, z = 0, s = 16;
  double vX = 0, vY = 0;
  double dir = 0;

private:
  double flipDirection = 0, targetFlipDirection = 0;
  fin::data::StlVector<fin::graphics::ImageTexture*> walkingTextures;
};
