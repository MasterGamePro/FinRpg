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
      auto* keyboard = get_input()->getKeyboard();

      while ( !get_main_window()->is_closed() ) {
        poll_inputs();

        keyboard->before_tick();
        tick();
        keyboard->after_tick();

        render();

        frame++;

        const uint64_t diff = stopwatch->get_current_ms();
        if ( diff >= 1000 ) {
          fps_ = frame;
          get_main_window()->set_title(algorithm::string_format("%d", fps_));
          frame = 0;
          stopwatch->reset();
        }

        const auto do_frame_cap = false;
        if ( do_frame_cap && frame >= 60 ) {
          fps_ = frame;
          frame = 0;
          time::Time::sleep_ms( 1000 - diff );
          get_main_window()->set_title(algorithm::string_format("%d", fps_));
        }
      }
    }

    void go_to_scene( IScene* scene ) {
      if ( this->scene_ != nullptr ) {
        delete this->scene_;
      }
      if ( this->scene_ != scene ) {
        this->scene_ = scene;
        scene->on_start( this );
      }
    }

    static IApp* instance() { return instance_; }

    virtual IWindow* get_main_window() = 0;

    protected:
    virtual void init() = 0;
    virtual void poll_inputs() = 0;
    virtual void deinit() = 0;

    private:
    void tick();
    void render();

    int fps_;

    IScene* scene_;
    static IApp* instance_;
  };
}
