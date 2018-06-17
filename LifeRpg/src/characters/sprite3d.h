#pragma once
#include "fin/graphics/texture.h"

class Sprite3d {

  void set_texture(fin::graphics::Texture texture) {
    texture_ = texture;
  }

  void set_direction() {
    
  }

  void set_floor_z() {
    
  }

  private:
  fin::graphics::Texture texture_;
  float direction_, floorZ_;
};
