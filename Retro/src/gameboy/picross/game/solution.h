#pragma once
#include "board.h"

namespace retro::gameboy::picross {
  class Solution {
    public:
    Solution(const Board solutionBoard) : solutionBoard(solutionBoard) {}

    Solution(const Solution& other) : solutionBoard(other.solutionBoard) {}

    bool check(const Board& gameBoard) const {
      return solutionBoard == gameBoard;
    }

    private:
    const Board solutionBoard;
  };
}
