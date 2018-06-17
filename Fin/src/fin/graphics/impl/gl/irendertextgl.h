#pragma once

#include "fin/graphics/irendertext.h"

namespace fin::graphics {
  class IRenderTextGl : public IRenderText {
    public:
    virtual void reload_context() = 0;
  };
}
