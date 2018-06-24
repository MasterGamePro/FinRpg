#pragma once
#include "fin/math/trig.h"
#include "rpg/scenes/mainmenu/mainmenuscene.h"
#include "optionsmenu.h"

void OptionsMenu::on_tick_control(fin::input::IInput* i) {
  const auto d = i->get_input_layout()->getPrimaryDirectionalInput();
  const auto a = i->get_input_layout()->getActionPressableInput();
  if (d->get_pressed_amount() > 0) {
    double dir = d->get_pressed_direction();
    const auto x = fin::math::cosd(dir), y = fin::math::sind(dir);
    if (abs(x) > abs(y)) {
      if (option == 0) {
        bool changed = false;
        if (x > 0 && selectedResolution < 2 - 1) {
          changed = true;
          selectedResolution++;
        }
        else if (x < 0 && selectedResolution > 0) {
          changed = true;
          selectedResolution--;
        }
        if (changed) {
          const int* resolution = resolutions[selectedResolution];
          window->set_size(resolution[0], resolution[1]);
        }
      }
    }
    else {
      if (y < 0 && option < optionCount - 1) {
        option++;
      }
      else if (y > 0 && option > 0) {
        option--;
      }
    }
  }
  else if (a->checkState(fin::input::PressableState::PRESSED)) {
    if (option == 1) {
      isFullscreen = !isFullscreen;
      window->toggle_fullscreen();
    }
    else if (option == 2) {
      this->app->go_to_scene(new MainMenuScene());
    }
  }
}