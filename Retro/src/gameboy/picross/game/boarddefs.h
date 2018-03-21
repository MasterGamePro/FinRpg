#pragma once

namespace retro::gameboy::picross {
  enum CellType {
    CELL_EMPTY,
    CELL_FILLED,
    CELL_BLANKED
  };

  typedef struct Cursor {
    int x, y;
  } Cursor;
}