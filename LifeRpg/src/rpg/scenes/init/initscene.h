#pragma once
#include "fin/app/iscene.h"
#include "rpg/scenes/mainmenu/mainmenuscene.h"
#include "rpg/ui/options/optionsmenu.h"
#include "fin/math/geometry/matrix3d.h"

class InitScene : public fin::app::IScene {
  void on_start(fin::app::IApp* app) override final {
    fin::debug::Log::println("InitScene.start() {");

    auto window = app->get_main_window();

    // TODO: Move to Options class.
    OptionsMenu::load_settings_static(app, window);

    app->go_to_scene(new MainMenuScene());
    fin::debug::Log::println("InitScene.start() }");
  }

  void on_end() override final { fin::debug::Log::println("InitScene.end()"); }
};
