#pragma once

namespace fin::input {
  class IPointingDevice {
    public:
    virtual ~IPointingDevice() {}

    virtual double getX() = 0;
    virtual double getY() = 0;
    virtual 
  };
}