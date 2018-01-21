#pragma once

#include "fin/app/iscene.h"
#include "fin/graphics/camera/camera.h"
#include "fin/graphics/view.h"
#include "characters/icharacter.h"
#include "characters/npc.h"
#include "characters/player.h"

class DebugVillageScene : public fin::app::IScene {
  void on_start( fin::app::IApp* app ) {
    fin::app::IWindow* window = app->get_main_window();
    fin::graphics::View* view = window->get_view();

    fin::graphics::Camera* camera = new fin::graphics::Camera();
    view->set_camera( camera );

    fin::app::Stage* stage = new fin::app::Stage();
    camera->set_stage( stage );

    stage->add_child( new Player( camera, app->get_graphics()->ts() ) );
    stage->add_child( new Npc( "player", app->get_graphics()->ts() ) );
  }
};