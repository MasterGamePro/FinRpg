#pragma once
#include "actor/iactor.h"

namespace fin {
  namespace app {
    class Stage : public IActor {
      protected:
      void on_tick_control( input::IInput* input ) override final {}
      void on_tick_physics() override final {}
      void on_tick_collision() override final {}
      void on_tick_animation() override final {}
      void on_tick_audio() override final {}
      void on_tick_render( graphics::IGraphics* graphics ) override final {}
    };
  }
}
