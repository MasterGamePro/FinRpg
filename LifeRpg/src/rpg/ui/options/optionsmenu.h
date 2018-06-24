#pragma once
#include "fin/algorithm/string/format.h"
#include "fin/app/iapp.h"
#include "fin/app/actor/iactor.h"
#include "fin/input/iinput.h"

// TODO: Create a common interface for options.
class OptionsMenu : public fin::app::IActor {
  public:
  OptionsMenu(fin::app::IApp* app, fin::app::IWindow* window) {
    this->app = app;
    this->window = window;
  }

  protected:
  void on_tick_control(fin::input::IInput* i) override final;

  void on_tick_physics() override final {

  }

  void on_tick_collision() override final {

  }

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
        for (int r = 0; r < 2; r++) {
          const int* resolution = resolutions[r];
          double vv = v * (r == selectedResolution ? 1 : .8);
          std::string s = fin::algorithm::format_string("%dx%d", resolution[0], resolution[1]);
          g->p()->color3d(vv, vv, vv);
          g->rt()->draw_string(s, rx, y);
          rx += s.length() * 8;
        }
      }
      else if (i == 1) {
        r2d->draw_rectangle(rx, y, lineHeight, lineHeight, isFullscreen);
        g->rt()->draw_string("Fullscreen", rx + lineHeight, y);
      }
      else if (i == 2) {
        g->rt()->draw_string("Back", rx, y);
      }
      y += lineHeight;
    }
  }

  private:
  fin::app::IApp* app;
  fin::app::IWindow* window;
  int option = 0, optionCount = 5;
  int selectedResolution = 1;
  bool isFullscreen = false;
  const int resolutions[3][2] = {{320, 240}, {640, 480}, {1920, 1080}};
};
