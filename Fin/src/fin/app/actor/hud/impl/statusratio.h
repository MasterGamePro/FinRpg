#pragma once
#include "fin/app/actor/hud/ifractionalstatus.h"

namespace fin::app {

  class StatusRatio : public IFractionalStatus {
    public:
    ~StatusRatio() override;

    void set_min(double min) override { this->min = min; }
    void set_value(double value) override { this->value = value; }
    void set_max(double max) override { this->max = max; }
    double get_min() override { return min; }
    double get_value() override { return value; }
    double get_max() override { return max; }
    double get_fraction() override { return value / (max - min); }

    double set_position(const double x, const double y) {
      this->x = x;
      this->y = y;
    }

    protected:
    void on_tick_control(input::IInput* input) override {}
    void on_tick_physics() override {}
    void on_tick_collision() override {}
    void on_tick_animation() override {}
    void on_tick_audio() override {}

    void on_tick_render(graphics::IGraphics* g) override {
      graphics::IRenderText* rt = g->rt();

      std::string text;
      sprintf(text, "%lf / %lf", min, value);
      rt->draw_string(, x, y);
    }

    private:
    double min, value, max;
    double x, y;
  };
}
