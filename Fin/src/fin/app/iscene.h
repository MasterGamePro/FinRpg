#pragma once

namespace fin::app {
  class IApp;

  class IScene {
    public:
    IScene() {}
    virtual ~IScene() {}

    virtual void on_start(IApp* app) = 0;
  };
}
