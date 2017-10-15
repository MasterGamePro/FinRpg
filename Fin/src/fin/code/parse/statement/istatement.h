#pragma once

namespace fin::code {
  class IStatement {
    public:
    virtual void evaluate() = 0;
  };
}