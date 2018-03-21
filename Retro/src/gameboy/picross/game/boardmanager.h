#pragma once

#include "fin/app/actor/iactor.h"

#include "board.h"
#include "boardcontrolcomponent.h"
#include "boardrendercomponent.h"
#include "imagesolutionloader.h"
#include "solution.h"

namespace retro::gameboy::picross {
  class BoardManager : public fin::app::IActor {
    public:
    BoardManager(const fin::io::File& file) {
      ImageSolutionLoader solutionLoader;
      solutionLoader.load(file, solution);

      add_component(new BoardControlComponent(&board, &cursor));
      add_component(new BoardRenderComponent(&board, &cursor));
    }

    ~BoardManager() {
    }

    private:
    Solution solution;
    Board board;
    Cursor cursor;
  };
}
