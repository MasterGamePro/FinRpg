#pragma once

#include "fin/app/iscene.h"
#include "fin/graphics/camera/camera.h"
#include "fin/graphics/view.h"
#include "ui/options/optionsmenu.h"

class DebugMenuScene : public fin::app::IScene {
  void on_start( fin::app::IApp* app ) {
    fin::app::IWindow* window = app->get_main_window();
    fin::graphics::View* view = window->get_view();

    fin::graphics::Camera* camera = new fin::graphics::Camera();
    view->set_camera( camera );

    fin::app::Stage* stage = new fin::app::Stage();
    camera->set_stage( stage );

    stage->add_child( new OptionsMenu(window) );
  }
};
