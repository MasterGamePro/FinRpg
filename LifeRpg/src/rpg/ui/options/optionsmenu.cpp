#include "fin/math/trig.h"
#include "rpg/scenes/mainmenu/mainmenuscene.h"
#include "optionsmenu.h"

// TODO: Refactor w/ handlers in UI framework once it's done.
void OptionsMenu::on_tick_control(fin::input::IInput* i) {
  const auto d = i->get_input_layout()->getPrimaryDirectionalInput();
  const auto a = i->get_input_layout()->getActionPressableInput();
  if (d->get_pressed_amount() > 0) {
    const auto dir = d->get_pressed_direction();
    const auto x = fin::math::cosd(dir);
    const auto y = fin::math::sind(dir);
    if (abs(x) > abs(y)) {
      if (option == 0) {
        auto changed = false;
        if (x > 0 && selectedResolution < resolutions.size() - 1) {
          changed = true;
          selectedResolution++;
        }
        else if (x < 0 && selectedResolution > 0) {
          changed = true;
          selectedResolution--;
        }
        if (changed) {
          const auto resolution = resolutions[selectedResolution];
          const auto width = resolution[0];
          const auto height = resolution[1];
          options_.set_resolution(width, height);
          save_settings();
          window->set_size(width, height);
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
      const auto newIsFullscreen = !options_.is_fullscreen();
      options_.toggle_fullscreen(newIsFullscreen);
      window->toggle_fullscreen(newIsFullscreen);
      save_settings();
    }
    else if (option == 2) {
      this->app->go_to_scene(new MainMenuScene());
    }
  }
}