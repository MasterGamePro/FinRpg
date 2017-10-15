#pragma once

namespace fin::input {
  class PointingDevice {
    public:

    virtual double getX() = 0;
    virtual double getY() = 0;
  };
}