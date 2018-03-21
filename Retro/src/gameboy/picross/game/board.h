#pragma once

#include <boost/mpl/assert.hpp>

#include "fin/debug/exception.h"

#include "boarddefs.h"

namespace retro::gameboy::picross {
  class Board {
    public:
    Board(const int width, const int height) : kWidth(width), kHeight(height) {
      cellArray = new CellType[width * height];
    }

    Board(const Board& other) : kWidth(other.kWidth), kHeight(other.kHeight) {
      cellArray = new CellType[kWidth * kHeight];
      for (auto y = 0; y < kHeight; y++) {
        for (auto x = 0; x < kWidth; x++) {
          set_cell(x, y, other.get_cell(x, y));
        }
      }
    }

    ~Board() {
      delete cellArray;
    }

    int get_width() const { return kWidth; }
    int get_height() const { return kHeight; }

    void set_cell(const int x, const int y, const CellType cellType) {
      assert_index(x, y);
      const auto index = get_index(x, y);
      if (cellArray[index] == CELL_EMPTY || cellType == CELL_EMPTY) {
        cellArray[index] = cellType;
      }
    }

    CellType get_cell(const int x, const int y) const {
      assert_index(x, y);
      return cellArray[get_index(x, y)];
    }

    bool operator==(const Board& other) const {
      if (kWidth != other.kWidth || kHeight != other.kHeight) {
        throw fin::debug::Exception("Board", "operator==", "This board (%d, %d) not same size as other board (%d %d).", kWidth, kHeight, other.kWidth, other.kHeight);
      }
      for (auto y = 0; y < kHeight; y++) {
        for (auto x = 0; x < kWidth; x++) {
          if (get_cell(x, y) != get_cell(x, y)) {
            return false;
          }
        }
      }
      return true;
    }

    private:
    int get_index(const int x, const int y) const {
      return y * kWidth + x;
    }

    void assert_index(const int x, const int y) const {
      if (x < 0 || x >= kWidth || y < 0 || y >= kHeight) {
        throw fin::debug::Exception("Board", "assert_index", "Index out of bounds: (%d, %d)", x, y);
      }
    }

    const int kWidth, kHeight;
    CellType * cellArray;
  };
}
