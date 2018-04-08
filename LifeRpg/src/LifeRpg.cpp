// LifeRpg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "fin/app/iapp.h"
#include "fin/app/impl/glfw/appglfw.h"
#include "fin/debug/log.h"
#include "scenes/debugvillagescene.h"
#include "scenes/debugmenuscene.h"

int main() {
  try {
    fin::debug::Log::print("Creating app... ");
    auto app = new fin::app::AppGlfw();
    fin::debug::Log::println("OK!");

    fin::debug::Log::print("Launching app... ");
    //app->launch(new DebugVillageScene());// new DebugMenuScene() );
    app->launch(new DebugMenuScene() );
    fin::debug::Log::println("OK!");

    fin::debug::Log::print("Freeing app data... ");
    delete app;
    fin::debug::Log::println("OK!\n");
  }
  catch (std::exception e) {
    fin::debug::Log::println(e.what());
    std::cin.ignore();
  }

  return 0;
}