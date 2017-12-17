// LifeRpg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "characters/icharacter.h"
#include "characters/player.h"
#include "fin/app/iapp.h"
#include "fin/app/impl/glfw/appglfw.h"
#include "fin/app/iwindow.h"
#include "fin/graphics/camera/camera.h"
#include "fin/graphics/view.h"
#include "fin/app/iscene.h"
#include "fin/debug/log.h"

class DebugScene : public fin::app::IScene {
  void on_start( fin::app::IApp* app ) {
    fin::app::IWindow* window = app->get_main_window();
    fin::graphics::View* view = window->get_view();

    fin::graphics::Camera* camera = new fin::graphics::Camera();
    view->set_camera( camera );

    fin::app::Stage* stage = new fin::app::Stage();
    camera->set_stage( stage );

    stage->add_child( new Player(camera, app->get_graphics()->ts()) );
  }
};

int main() {
  try {
    fin::debug::Log::print( "Creating app... " );
    auto app = new fin::app::AppGlfw();
    fin::debug::Log::println( "OK!" );

    fin::debug::Log::print( "Launching app... " );
    app->launch( new DebugScene() );
    fin::debug::Log::println( "OK!" );

    fin::debug::Log::print( "Freeing app data... " );
    delete app;
    fin::debug::Log::println( "OK!\n" );
  } catch ( std::exception e ) {
    fin::debug::Log::println( e.what() );
    std::cin.ignore();
  }

  return 0;
}