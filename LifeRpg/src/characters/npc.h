#pragma once
#include "icharacter.h"
#include "fin/graphics/camera/camera.h"
#include "fin/input/iinput.h"
#include "fin/time/countdowntimer.h"

enum class NpcState {
  STANDING,
  WALKING
};

class Npc : public ICharacter {
  public:
  Npc(std::string name, fin::graphics::ITextures* ts) : ICharacter(name, ts) {
    initX = 0;
    initY = 0;
  }

  void on_tick_control(fin::input::IInput* i) override final {
    if(state == NpcState::STANDING) {
      if(standTimer_.is_done()) {
        state = NpcState::WALKING;
        const auto radius = fin::math::randomd(0, 48);
        const auto dir = fin::math::randomd(0, 360);
        toX = initX + fin::math::cosd(dir) * radius;
        toY = initY + fin::math::sind(dir) * radius;
        standTimer_.stop();
      }
    } else if(state == NpcState::WALKING) {
      if (move_towards(toX, toY, .4)) {
        state = NpcState::STANDING;
        standTimer_.set_duration_ms(fin::math::randomd(2, 4) * 1000);
        standTimer_.reset();
        standTimer_.start();
      }
    }
  }

  private:
  fin::graphics::Camera* camera;

  NpcState state = NpcState::STANDING;
  fin::time::CountdownTimer standTimer_;
  float initX, initY;
  float toX, toY;
};
