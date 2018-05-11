#pragma once
#include <cstdint>

namespace recom::bin::gb {

  uint8_t& get(uint16_t address) {
    if (address >= 0xE000 && address <= 0xFE00) {
      const auto relativeAddress = address - 0xE000;

    }
  }
}
