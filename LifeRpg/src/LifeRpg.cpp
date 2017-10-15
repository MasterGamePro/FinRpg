// LifeRpg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "fin/audio/iaudio.h"
#include "fin/app/impl/glfw/appglfw.h"

#include "characters/character.h"
#include "fin/app/iwindow.h"
#include "fin/app/iapp.h"
#include "fin/graphics/view.h"
#include "fin/graphics/camera.h"
#include "fin/debug/log.h"
#include "fin/app/iscene.h"

class DebugScene : public fin::app::IScene {
  void on_start( fin::app::IApp* app ) {
    fin::app::IWindow* window = app->get_main_window();
    fin::graphics::View* view = window->get_view();

    fin::graphics::Camera* camera = new fin::graphics::Camera();
    view->set_camera( camera );

    fin::app::Stage* stage = new fin::app::Stage();
    camera->set_stage( stage );

    stage->add_child( new Character() );
  }
};

int main() {
  try {
    fin::log::Log::print( "Creating app... " );
    auto app = new fin::app::AppGlfw();
    fin::log::Log::println( "OK!" );

    fin::log::Log::print( "Launching app... " );
    app->launch( new DebugScene() );
    fin::log::Log::println( "OK!" );

    /*fin::log::Log::print( "Creating window... " );
    fin::app::IWindow* window = app->get_window();
    window->set_title( "Hello world!" );
    window->set_size( 640, 480 );
    fin::log::Log::println( "OK!\n" );
    fin::app::IActor* a = new Character();*/

    fin::log::Log::print( "Freeing app data... " );
    delete app;
    fin::log::Log::println( "OK!\n" );
  } catch ( std::exception e ) {
    fin::log::Log::println( e.what() );
    std::cin.ignore();
  }

  return 0;
}