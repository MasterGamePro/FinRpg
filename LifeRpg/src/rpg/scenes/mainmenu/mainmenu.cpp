#include "stdafx.h"
#include "fin/math/trig.h"
#include "rpg/scenes/debugvillagescene.h"
#include "rpg/scenes/optionsmenu/optionsmenuscene.h"
#include "mainmenu.h"

void MainMenu::on_tick_control(fin::input::IInput* i) {
  const auto d = i->get_input_layout()->getPrimaryDirectionalInput();
  const auto a = i->get_input_layout()->getActionPressableInput();
  if (d->get_pressed_amount() > 0) {
    const auto dir = d->get_pressed_direction();
    const auto x = fin::math::cosd(dir);
    const auto y = fin::math::sind(dir);
    if (abs(y) > abs(x)) {
      if (y < 0 && option < optionCount - 1) { option++; }
      else if (y > 0 && option > 0) { option--; }
    }
  }
  else if (a->checkState(fin::input::PressableState::PRESSED)) {
    if (option == 0) { this->app->go_to_scene(new DebugVillageScene()); }
    else if (option == 1) { this->app->go_to_scene(new OptionsMenuScene()); }
  }
}
