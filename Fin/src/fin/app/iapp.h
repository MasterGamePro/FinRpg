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
    virtual ~IApp() {}

    virtual input::IInput* get_input() const = 0;
    virtual audio::IAudio* get_audio() const = 0;
    virtual graphics::IGraphics* get_graphics() const = 0;

    void launch(IScene* initialScene) {
      init();
      get_graphics()->init();
      go_to_scene_immediately(initialScene);

      int frame = 0;

      auto stopwatch = new time::Stopwatch();
      auto* input = get_input();

      while (!get_main_window()->is_closed()) {
        poll_inputs();

        input->before_tick();
        tick();
        input->after_tick();

        render();

        frame++;

        const uint64_t diff = stopwatch->get_current_ms();
        if (diff >= 1000) {
          fps_ = frame;
          get_main_window()->set_title(algorithm::string_format("%d", fps_));
          frame = 0;
          stopwatch->reset();
        }

        const auto do_frame_cap = false;
        if (do_frame_cap && frame >= 60) {
          fps_ = frame;
          frame = 0;
          time::Time::sleep_ms(1000 - diff);
          get_main_window()->set_title(algorithm::string_format("%d", fps_));
        }

        if (next_scene_ != nullptr) {
          go_to_scene_immediately(next_scene_);
          next_scene_ = nullptr;
        }
      }
    }

    void go_to_scene(IScene* scene) {
      if (this->scene_ == nullptr) {
        go_to_scene_immediately(scene);
      }
      else {
        next_scene_ = scene;
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
    void go_to_scene_immediately(IScene* scene) {
      if (this->scene_ != nullptr) {
        this->scene_->on_end();
        delete this->scene_;
      }
      this->scene_ = scene;
      this->scene_->on_start(this);
    }

    int fps_;

    IScene *scene_, *next_scene_;
    static IApp* instance_;
  };
}
