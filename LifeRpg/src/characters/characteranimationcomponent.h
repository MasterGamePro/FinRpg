#pragma once

#include "fin/app/components/animation/ianimationcomponent.h"

enum CharacterAnimationType {
  CHARACTERANIMATION_STAND,
  CHARACTERANIMATION_WALK
};

class CharacterAnimationComponent : fin::app::IAnimationComponent {
public:
  void tick_animation() override final {

  }

  bool switch_animation(CharacterAnimationType newType) {

  }

private:
  CharacterAnimationType animation = CHARACTERANIMATION_STAND;
};
