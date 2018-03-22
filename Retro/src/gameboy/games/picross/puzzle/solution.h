#pragma once
#include "board.h"

namespace retro::gameboy::picross {
  class Solution {
    public:
    Solution(const Board solutionBoard) : solutionBoard(solutionBoard) {}

    Solution(const Solution& other) : solutionBoard(other.solutionBoard) {}

    int get_width() const { return solutionBoard.get_width(); }
    int get_height() const { return solutionBoard.get_height(); }

    bool check(const Board& gameBoard) const {
      return solutionBoard == gameBoard;
    }

    private:
    const Board solutionBoard;
  };
}
