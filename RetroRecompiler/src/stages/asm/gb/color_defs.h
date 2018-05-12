#pragma once
#include "fin/graphics/igraphics.h"

namespace recom::bin::gb {
  const fin::graphics::Color
    kBlack = fin::graphics::Color::from_rgb_b(0, 0, 0),
    kDarkGray = fin::graphics::Color::from_rgb_b(96, 96, 96),
    kLightGray = fin::graphics::Color::from_rgb_b(192, 192, 192),
    kWhite = fin::graphics::Color::from_rgb_b(255, 255, 255);
}
