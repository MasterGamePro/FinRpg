#pragma once

#include "fin/app/iscene.h"
#include "ui/options/optionsmenu.h"

class DebugMenuScene : public fin::app::IScene {
  void on_start( fin::app::IApp* app ) override final {
    auto window = app->get_main_window();
    auto view = window->get_view();

    const auto camera = new fin::graphics::Camera();
    view->set_camera( camera );

    const auto stage = new fin::app::Stage();
    camera->set_stage( stage );

    stage->add_child( new OptionsMenu(app, window) );
  }
};
