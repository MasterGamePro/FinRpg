#pragma once

namespace fin::input {
  class PointingDevice {
    public:
    virtual ~IPointingDevice() {}

    virtual double getX() = 0;
    virtual double getY() = 0;
  };
}