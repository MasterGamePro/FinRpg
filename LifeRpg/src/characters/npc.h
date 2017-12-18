#pragma once
#include "icharacter.h"
#include "fin/graphics/camera/camera.h"
#include "fin/input/iinput.h"

class Npc : public ICharacter {
public:
  Npc(std::string name, fin::graphics::ITextures* ts) : ICharacter(name, ts) {}

  void on_tick_control(fin::input::IInput* i) override final {}

private:
  fin::graphics::Camera* camera;
};
