#pragma once
#include "fin/app/iscene.h"
#include "fin/app/stage.h"
#include "fin/graphics/camera/camera.h"
#include "fin/graphics/view.h"
#include "mainmenu.h"

class MainMenuScene : public fin::app::IScene {
  void on_start(fin::app::IApp* app) override final {
    fin::debug::Log::println("MainMenuScene.start() {");

    auto window = app->get_main_window();
    auto view = window->get_view();

    const auto camera = new fin::graphics::Camera();
    view->set_camera(camera);

    const auto stage = new fin::app::Stage();
    camera->set_stage(stage);

    stage->add_child(new MainMenu(app, window));

    fin::debug::Log::println("MainMenuScene.start() }");
  }

  void on_end() override final {
    // TODO: Delete the stage.
    fin::debug::Log::println("MainMenuScene.end()");
  }
};
