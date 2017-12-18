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
    const auto amt = pdi->getHeldAmount();

    fin::debug::Log::println("camdir: %lf", camera->get_normal().xy_dird());

    if (amt > 0) {
      dir = camera->get_normal().xy_dird() - 90 + pdi->getHeldDirection();
      isMoving = true;
    }
    else {
      isMoving = false;
    }

    x += fin::math::Trig::cosd(dir) * amt;
    y += fin::math::Trig::sind(dir) * amt;
  }

  void on_tick_animation() override final {
    ICharacter::on_tick_animation();

    fin::math::Point3d *from = &camera->get_from_point(),
      *to = &camera->get_to_point();

    double zd = 16;

    to->x(x);
    to->y(y);
    to->z(z + zd);

    from->x(x);
    from->y(y + 96);
    from->z(z + zd + 8);
  }

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override final {
    g->p()->color3d(1, 1, 1);
    g->rt()->draw_string("The quick, brown fox jumps over the lazy dog.", 0, 0);
    g->rt()->draw_string(fin::algorithm::string_format("Memory: %d b", fin::debug::totalBytes), 0, 20);
  }

private:
  fin::graphics::Camera* camera;
};
