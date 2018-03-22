#pragma once

#include "fin/app/components/control/icontrolcomponent.h"
#include "fin/input/iinput.h"
#include "fin/math/common.h"

#include "board.h"

namespace retro::gameboy::picross {
  class BoardControlComponent : public fin::app::IControlComponent {
    public:
    BoardControlComponent(Board* board, Cursor* cursor) :
      board(board), cursor(cursor) {}

    void tick_control(fin::input::IInput* input) override final {
      auto inputLayout = input->get_input_layout();
      auto pdi = inputLayout->getPrimaryDirectionalInput();

      // TODO: Write buffer class to delay hold movement for a couple seconds.
      if (pdi->get_pressed_amount() > .9) {
        const auto pressDir = fin::math::
            round_to_nearest(pdi->get_pressed_direction(), 45.),
          xAmt = fin::math::Trig::cosd(pressDir),
          yAmt = -fin::math::Trig::sind(pressDir);
        auto x = cursor->x,
          y = cursor->y;
        x += xAmt;
        y += yAmt;
        cursor->x = fin::math::contain(0, x, board->get_width() - 1);
        cursor->y = fin::math::contain(0, y, board->get_height() - 1);
      }

      if (inputLayout->getActionPressableInput()->
                       checkState(fin::input::PRESSABLESTATE_PRESSED)) {
        board->set_cell(cursor->x, cursor->y, CELL_FILLED);
      }
      else if (inputLayout->getCancelPressableInput()->
                            checkState(fin::input::PRESSABLESTATE_PRESSED)) {
        board->set_cell(cursor->x, cursor->y, CELL_FILLED);
      }
    }

    private:
    Board* board;
    Cursor* cursor;
  };
}
