#pragma once

#include "fin/app/iscene.h"
#include "fin/graphics/camera/camera.h"
#include "characters/icharacter.h"
#include "characters/npc.h"
#include "characters/player.h"

class DebugVillageScene : public fin::app::IScene {
  void on_start( fin::app::IApp* app ) override final {
    const auto window = app->get_main_window();
    const auto view = window->get_view();

    const auto camera = new fin::graphics::Camera();
    view->set_camera( camera );

    const auto stage = new fin::app::Stage();
    camera->set_stage( stage );

    stage->add_child( new Player( camera, app->get_graphics()->ts() ) );
    stage->add_child( new Npc( "player", app->get_graphics()->ts() ) );
  }

  void on_end() override final {
    // TODO: Delete the stage.
  }
};