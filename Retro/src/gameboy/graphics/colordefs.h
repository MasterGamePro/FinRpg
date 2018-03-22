#pragma once
#include "fin/graphics/color.h"

namespace retro::gameboy {
  const fin::graphics::Color
    kWhite = fin::graphics::Color::from_rgb_b(255, 255, 255),
    kLightGray = fin::graphics::Color::from_rgb_b(170, 170, 170),
    kDarkGray = fin::graphics::Color::from_rgb_b(85, 85, 85),
    kBlack = fin::graphics::Color::from_rgb_b(0, 0, 0);
}
