#pragma once

#include "fin/app/components/render/irendercomponent.h"

#include "board.h"

namespace retro::gameboy::picross {
  class BoardRenderComponent : public fin::app::IRenderComponent {
    public:
    BoardRenderComponent(const Board* board, const Cursor* cursor) :
      board(board), cursor(cursor) {}

    void tick_render(fin::graphics::IGraphics* g) override final {
      const auto r2d = g->r2d();
      const auto p = g->p();
      for (auto y = 0; y < board->get_height(); ++y) {
        for (auto x = 0; x < board->get_width(); ++x) {
          CellType type = board->get_cell(x, y);
          switch (type) {
            case CELL_EMPTY:
              p->color3d(0, 0, 0);
              break;
            case CELL_BLANKED:
              p->color3d(128, 128, 128);
              break;
            case CELL_FILLED:
              p->color3d(255, 255, 255);
              break;
          }
          r2d->fill_rectangle(x*cellSize, y*cellSize, cellSize, cellSize);
        }
      }
    }

    private:
    const Board * board;
    const Cursor* cursor;
    int cellSize = 16;
  };
}
