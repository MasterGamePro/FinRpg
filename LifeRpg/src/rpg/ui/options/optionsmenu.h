#pragma once
#include <array>
#include <json/json.h>
#include "fin/algorithm/string/format.h"
#include "fin/app/iapp.h"
#include "fin/app/actor/iactor.h"
#include "fin/input/iinput.h"
#include "rpg/save/options/util.h"

// TODO: Create a common interface for options.
class OptionsMenu : public fin::app::IActor {
  public:
  OptionsMenu(fin::app::IApp* app, fin::app::IWindow* window) {
    this->app = app;
    this->window = window;
    load_settings();
  }

  // TODO: Move to external Options class.
  static void load_settings_static(fin::app::IApp* app,
                                   fin::app::IWindow* window) {
    OptionsMenu menu(app, window);
    menu.load_settings();
  }

  protected:
  void on_tick_control(fin::input::IInput* i) override final;

  void on_tick_physics() override final { }

  void on_tick_collision() override final { }

  void on_tick_animation() override {}
  void on_tick_audio() override final {}

  void on_tick_render_perspective(fin::graphics::IGraphics* g) override final {}

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override {
    auto r2d = g->r2d();

    g->p()->color3d(0, 0, .2);
    g->r2d()->fill_rectangle(0, 0, 320, 240);
    g->p()->color3d(0, .2, 0);
    g->r2d()->fill_rectangle(0, 240, 320, 240);
    g->p()->color3d(.2, 0, 0);
    g->r2d()->fill_rectangle(320, 240, 320, 240);
    g->p()->color3d(.2, 0, .2);
    g->r2d()->fill_rectangle(320, 0, 320, 240);

    double padding = 30;
    double lineHeight = 20;
    double x = padding, y = padding;
    for (int i = 0; i < optionCount; i++) {
      double pointRad;
      double v;
      if (i == option) {
        v = 1;
        pointRad = lineHeight / 2;
      }
      else {
        v = .8;
        pointRad = lineHeight / 3;
      }
      g->p()->color3d(v, v, v);
      r2d->drawCircle(x + lineHeight / 2, y + lineHeight / 2, pointRad, true);
      double rx = x + lineHeight;
      if (i == 0) {
        for (int r = 0; r < resolutions.size(); r++) {
          const auto resolution = resolutions[r];
          double vv = v * (r == selectedResolution ? 1 : .8);
          std::string s = fin::algorithm::format_string("%dx%d", resolution[0],
                                                        resolution[1]);
          g->p()->color3d(vv, vv, vv);
          g->rt()->draw_string(s, rx, y);
          rx += s.length() * 8;
        }
      }
      else if (i == 1) {
        r2d->draw_rectangle(rx, y, lineHeight, lineHeight,
                            options_.is_fullscreen());
        g->rt()->draw_string("Fullscreen", rx + lineHeight, y);
      }
      else if (i == 2) { g->rt()->draw_string("Back", rx, y); }
      y += lineHeight;
    }
  }

  private:
  void load_settings() {
    if (read_options_from_file(options_, file_)) {
      const auto optionsWidth = options_.get_width();
      const auto optionsHeight = options_.get_height();
      for (int r = 0; r < resolutions.size(); r++) {
        const auto resolution = resolutions[r];
        if (resolution[0] == optionsWidth && resolution[1] == optionsHeight) {
          selectedResolution = r;
          break;
        }
      }
      apply_settings();
    }
  }

  void save_settings() { write_options_to_file(options_, file_); }

  void apply_settings() {
    window->set_size_and_fullscreen(options_.get_width(), options_.get_height(),
                                    options_.is_fullscreen());
  }

  fin::io::File file_ = fin::io::File("saves/options.dat");
  fin::app::IApp* app;
  fin::app::IWindow* window;
  int option = 0, optionCount = 5;
  int selectedResolution = 1;
  const std::vector<std::array<int, 2>> resolutions{
    {320, 240}, {640, 480}, {1280, 720}, {1400, 900}, {1600, 900}, {1920, 1080}
  };
  rpg::save::Options options_;
};
