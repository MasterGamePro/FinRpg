#pragma once
#include "icharacter.h"
#include "fin/graphics/camera/camera.h"
#include "fin/input/iinput.h"

class Npc : public ICharacter {
  public:
  Npc( std::string name, fin::graphics::ITextures* ts ) : ICharacter( name, ts ) {
    ADD_TO_TOTAL_MEMORY_CHILD( Npc, ICharacter );
  }
  ~Npc() {
    REMOVE_FROM_TOTAL_MEMORY_CHILD( Npc, ICharacter );
  }

  void on_tick_control( fin::input::IInput* i ) override final {}

  private:
  fin::graphics::Camera* camera;
};
