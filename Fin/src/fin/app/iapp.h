#pragma once

#include "fin/audio/iaudio.h"
#include "fin/graphics/igraphics.h"
#include "iwindow.h"
#include "fin/input/iinput.h"
#include "fin/time/stopwatch.h"
#include "iscene.h"

namespace fin::app {
  class IApp {
    public:

    IApp();
    ~IApp();

    virtual input::IInput* get_input() const = 0;
    virtual audio::IAudio* get_audio() const = 0;
    virtual graphics::IGraphics* get_graphics() const = 0;

    void launch( IScene* initialScene ) {
      init();
      get_graphics()->init();
      initialScene->on_start( this );

      int frame = 0;

      auto stopwatch = new time::Stopwatch();
      input::IKeyboard* keyboard = get_input()->getKeyboard();

      while ( true ) {
        poll_inputs();

        keyboard->before_tick();
        tick();
        keyboard->after_tick();

        render();

        frame++;

        long diff = stopwatch->get_current_ms();
        if ( diff >= 1000 ) {
          fps = frame;
          get_main_window()->set_title(algorithm::string_format("%d", fps));
          frame = 0;
          stopwatch->reset();
        }

        bool doFrameCap = false;
        if ( doFrameCap && frame >= 60 ) {
          fps = frame;
          frame = 0;
          time::Time::sleep_ms( 1000 - diff );
          get_main_window()->set_title(algorithm::string_format("%d", fps));
        }
      }
    }

    void go_to_scene( IScene* scene ) {
      if ( this->scene != nullptr ) {
        delete this->scene;
      }
      if ( this->scene != scene ) {
        this->scene = scene;
        scene->on_start( this );
      }
    }

    static IApp* instance() { return _instance; }

    virtual IWindow* get_main_window() = 0;

    protected:
    virtual void init() = 0;
    virtual void poll_inputs() = 0;
    virtual void deinit() = 0;

    private:
    void tick();
    void render();

    int fps;

    IScene* scene;
    static IApp* _instance;
  };
}
