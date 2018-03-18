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
    const auto il = i->getInputLayout();

    const auto pdi = il->getPrimaryDirectionalInput();
    const auto moveAmt = pdi->getHeldAmount();

    move(moveAmt, camera->get_normal().xy_dird() - 90 + pdi->getHeldDirection());

    const auto sdi = il->getSecondaryDirectionalInput();
    lookAmt = sdi->getHeldAmount();
    if (lookAmt > 0) {
      lookDir = sdi->getHeldDirection();
    }
  }

  void on_tick_animation() override final {
    ICharacter::on_tick_animation();

    fin::math::Point3d *from = &camera->get_from_point(),
      *to = &camera->get_to_point();

    double fov = 20;

    camera->set_field_of_view(fov);

    double zd = 16 * .6;

    double percent = .75;
    double w = 16;

    double camW = w / percent;
    double camDis = fin::math::Trig::tand(fov) / camW,
      camDir = 90,
      xd = camDis * fin::math::Trig::cosd(camDir),
      yd = camDis * fin::math::Trig::sind(camDir),
      lookDis = 8 * lookAmt,
      xp = lookDis * fin::math::Trig::cosd(lookDir) * fin::math::Trig::cosd(camDir + 90),
      yp = lookDis * fin::math::Trig::cosd(lookDir) * fin::math::Trig::sind(camDir + 90),
      zp = lookDis * fin::math::Trig::sind(lookDir);

    to->x(x + xp);
    to->y(y + yp);
    to->z(z + zd + zp);   ;

    from->x(x + xd + xp);
    from->y(y + yd + yp);
    from->z(z + zd + zp);
  }

  void on_tick_render_perspective(fin::graphics::IGraphics* g) override {
    ICharacter::on_tick_render_perspective(g);

    if (lookAmt > 0) {
      auto *t = g->t();
      t->identity();
      t->translate(x, y, z + 12);
      t->rotate_z(camera->get_normal().xy_dird() - 90);
      t->translate(0, -2, 0);
      t->rotate_y(-lookDir);
      t->translate(lookAmt * 8, 0, 0);
      g->p()->color3d(1, 0, 0);
      g->r3d()->draw_wall(-1, 0, 2, 1, 0, -2);
      g->p()->color3d(1, 1, 1);
    }
  }

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override final {
    g->p()->color3d(1, 1, 1);
    g->rt()->draw_string("The quick, brown fox jumps over the lazy dog.", 0, 0);
  }

  private:
  fin::graphics::Camera* camera;
  double lookAmt, lookDir;
};
