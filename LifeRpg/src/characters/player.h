#pragma once
#include "icharacter.h"
#include "fin/graphics/camera/camera.h"
#include "fin/input/iinput.h"

class Player : public ICharacter {
  public:
  Player(fin::graphics::Camera* camera, fin::graphics::ITextures* ts) : ICharacter("player", ts) {
    this->camera = camera;
  }

  void on_tick_control(fin::input::IInput* i) override final {
    const auto il = i->get_input_layout();

    const auto pdi = il->getPrimaryDirectionalInput();
    const auto moveAmt = fix_stick_range(pdi->get_held_amount());

    move(moveAmt, camera->get_normal().xy_dird() - 90 + pdi->get_held_direction());

    const auto sdi = il->getSecondaryDirectionalInput();
    lookAmt = fix_stick_range(sdi->get_held_amount());
    if (lookAmt > 0) {
      lookDir = sdi->get_held_direction();
    }
  }

  void on_tick_animation() override final {
    ICharacter::on_tick_animation();

    fin::math::Point3d *from = &camera->get_from_point(),
      *to = &camera->get_to_point();

    double fov = 45;

    camera->set_field_of_view(fov);

    double percent = .9; // .75 // Percent of screen to take up.
    double w = 16; // Size of character, do not modify.

    double camW = w / percent;
    double camDis = camW / 2 / fin::math::tand(fov / 2),
      camDir = 90,
      lookUnit = camW * .35,
      xLookDis = 1.5 * lookUnit * lookAmt,
      yLookDis = lookUnit * lookAmt,
      xd = camDis * fin::math::cosd(camDir),
      yd = camDis * fin::math::sind(camDir),
      zd = 2 * .6 * lookUnit,
      xp = xLookDis * fin::math::cosd(lookDir) * fin::math::cosd(camDir + 90),
      yp = xLookDis * fin::math::cosd(lookDir) * fin::math::sind(camDir + 90),
      zp = yLookDis * fin::math::sind(lookDir);

    const auto x_ = positionData_->p_x();
    const auto y_ = positionData_->p_y();
    const auto z_ = positionData_->p_z();

    to->x(x_ + xp);
    to->y(y_ + yp);
    to->z(z_ + zd + zp);

    from->x(x_ + xd + xp);
    from->y(y_ + yd + yp);
    from->z(z_ + zd + zp);
  }

  void on_tick_render_perspective(fin::graphics::IGraphics* g) override {
    ICharacter::on_tick_render_perspective(g);

    if (lookAmt > 0) {
      double w = 16;
      auto *t = g->t();
      t->identity();
      t->translate(positionData_->p_xyz());
      t->translate(0, 0, w * .6);
      t->rotate_z(camera->get_normal().xy_dird() - 90);
      t->translate(0, -2, 0);
      t->rotate_y(-lookDir);
      t->translate(lookAmt * 8, 0, 0);
      g->p()->color3d(1, 0, 0);
      const double s = .5;
      t->scale(s, s, s + 2 * lookAmt);
      g->r3d()->draw_wall(-1, 0, 1, 1, 0, -1);
      g->p()->color3d(1, 1, 1);
    }
  }

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override final {
    g->p()->color3d(1, 1, 1);
    g->rt()->draw_string("The quick, brown fox jumps over the lazy dog.", 0, 0);
  }

  private:
  double fix_stick_range(double amt) {
    const double error = .05, min = error, max = 1 - error;
    return (amt - min) / (max - min);
  }

  fin::graphics::Camera* camera;
  double lookAmt, lookDir;
};
