#pragma once
#include "render2d.h"
#include "irendertext.h"
#include <algorithm>

namespace fin::graphics {
  class RenderVectorText : public IRenderText {
    public:
    RenderVectorText(Render2d* r2d) {}

    void draw_char(char c, double x, double y, double w, double h) override final {
      c = toupper(c);

      const double lx = x, mx = x + .5*w, rx = x + w, ty = y, my = y + .5*h, by = y + h;
      const double cs = std::min(w, h) / 4;
      const double lcx = lx + cs, rcx = rx - cs, tcy = ty + cs, mtcy = my - cs / 2, mbcy = my + cs / 2, bcy = by - cs;

      double lw = 1;

      // Bold
      if (false) {
        lw = 2;
      }

      // Italics

      switch (c) {
        case '0':
          r2d->drawLine(lx, tcy, lcx, ty, lw);
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, lx, bcy, lw);
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rx, tcy, lw);
          r2d->drawLine(lx, bcy, rx, tcy, lw);
          break;

        case '1':
          r2d->drawLine(mx, by, mx, ty, lw);
          r2d->drawLine(lcx, tcy, mx, ty, lw);
          break;

        case '2':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(rx, my, rx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(lx, by, lx, my, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;

        case '3':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          r2d->drawLine(rx, by, rx, ty, lw);
          break;

        case '4':
          r2d->drawLine(lx, my, lx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, by, rx, ty, lw);
          break;

        case '5':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(lx, my, lx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, by, rx, my, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;

        case '6':
          r2d->drawLine(lx, by, lx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, by, rx, my, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;

        case '7':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(rx, by, rx, ty, lw);
          break;

        case '8':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(lx, by, lx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, by, rx, ty, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;

        case '9':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(lx, my, lx, ty, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, by, rx, ty, lw);
          break;

        case ':':
          r2d->drawLine(lx, bcy, lx, by, lw);
          r2d->drawLine(lx, mtcy, lx, my, lw);
          break;

        case '.':
          r2d->drawLine(lx, bcy, lx, by, lw);
          break;

        case ',':
          r2d->drawLine(lx, bcy, lx, by, lw);
          r2d->drawLine(lx - cs / 2, by + cs / 2, lx, by, lw);
          break;

        case 'A':
          r2d->drawLine(lx, tcy, lcx, ty, lw);
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, lx, by, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, tcy, rx, by, lw);
          break;

        case 'B':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(rx, tcy, rx, mtcy, lw);
          r2d->drawLine(lx, my, rcx, my, lw);
          r2d->drawLine(rx, mtcy, rcx, my, lw);
          r2d->drawLine(rx, mbcy, rcx, my, lw);
          r2d->drawLine(rx, mbcy, rx, bcy, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(lx, by, rcx, by, lw);
          break;

        case 'C':
          r2d->drawLine(lx, tcy, lcx, ty, lw);
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, lx, bcy, lw);
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          break;

        case 'D':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(rx, tcy, rx, bcy, lw);
          r2d->drawLine(lx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          break;

        case 'E':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(lx, my, mx, my, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;

        case 'F':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(lx, my, mx, my, lw);
          break;

        case 'G':
          r2d->drawLine(lx, tcy, lcx, ty, lw);
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, lx, bcy, lw);
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rx, my, lw);
          r2d->drawLine(mx, my, rx, my, lw);
          break;

        case 'H':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, my, rx, my, lw);
          r2d->drawLine(rx, ty, rx, by, lw);
          break;

        case 'I':
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(mx, ty, mx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          break;

        case 'J':
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rx, ty, lw);
          break;

        case 'K':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, my, rcx, my, lw);
          r2d->drawLine(rcx, my, rx, tcy, lw);
          r2d->drawLine(rx, tcy, rx, ty, lw);
          r2d->drawLine(rcx, my, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rx, by, lw);
          break;

        case 'L':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;

        case 'M':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, tcy, mx, bcy, lw);
          r2d->drawLine(mx, bcy, rx, tcy, lw);
          r2d->drawLine(rx, ty, rx, by, lw);
          break;

        case 'N':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, tcy, rx, bcy, lw);
          r2d->drawLine(rx, ty, rx, by, lw);
          break;

        case 'O':
          r2d->drawLine(lx, tcy, lcx, ty, lw);
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, lx, bcy, lw);
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rx, tcy, lw);
          break;

        case 'P':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(rx, tcy, rx, mtcy, lw);
          r2d->drawLine(lx, my, rcx, my, lw);
          r2d->drawLine(rx, mtcy, rcx, my, lw);
          break;

        case 'Q':
          r2d->drawLine(lx, tcy, lcx, ty, lw);
          r2d->drawLine(lcx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, lx, bcy, lw);
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rx, tcy, lw);
          r2d->drawLine(rcx, bcy, rx, ty, lw);
          break;

        case 'R':
          r2d->drawLine(lx, ty, lx, by, lw);
          r2d->drawLine(lx, ty, rcx, ty, lw);
          r2d->drawLine(rcx, ty, rx, tcy, lw);
          r2d->drawLine(rx, tcy, rx, mtcy, lw);
          r2d->drawLine(lx, my, rcx, my, lw);
          r2d->drawLine(rx, mtcy, rcx, my, lw);
          r2d->drawLine(rcx, my, rx, by, lw);
          break;

        case 'S':
          r2d->drawLine(rx, tcy, rcx, ty, lw);
          r2d->drawLine(rcx, ty, lcx, ty, lw);
          r2d->drawLine(lcx, ty, lx, tcy, lw);
          r2d->drawLine(lx, tcy, lcx, my, lw);
          r2d->drawLine(lcx, my, rcx, my, lw);
          r2d->drawLine(rcx, my, rx, bcy, lw);
          r2d->drawLine(rx, bcy, rcx, by, lw);
          r2d->drawLine(rcx, by, lcx, by, lw);
          r2d->drawLine(lcx, by, lx, bcy, lw);
          break;

        case 'T':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(mx, ty, mx, by, lw);
          break;

        case 'U':
          r2d->drawLine(lx, ty, lx, bcy, lw);
          r2d->drawLine(lx, bcy, lcx, by, lw);
          r2d->drawLine(lcx, by, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, bcy, lw);
          r2d->drawLine(rx, ty, rx, bcy, lw);
          break;

        case 'V':
          r2d->drawLine(lx, ty, lx, tcy, lw);
          r2d->drawLine(lx, tcy, mx, by, lw);
          r2d->drawLine(mx, by, rx, tcy, lw);
          r2d->drawLine(rx, ty, rx, tcy, lw);
          break;

        case 'W':
          r2d->drawLine(lx, ty, lx, tcy, lw);
          r2d->drawLine(lx, tcy, lcx, by, lw);
          r2d->drawLine(lcx, by, mx, tcy, lw);
          r2d->drawLine(mx, ty, mx, tcy, lw);
          r2d->drawLine(mx, tcy, rcx, by, lw);
          r2d->drawLine(rcx, by, rx, tcy, lw);
          r2d->drawLine(rx, ty, rx, tcy, lw);
          break;

        case 'X':
          r2d->drawLine(lx, ty, lx, tcy, lw);
          r2d->drawLine(rx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, rx, bcy, lw);
          r2d->drawLine(rx, tcy, lx, bcy, lw);
          r2d->drawLine(lx, by, lx, bcy, lw);
          r2d->drawLine(rx, by, rx, bcy, lw);
          break;

        case 'Y':
          r2d->drawLine(lx, ty, lx, tcy, lw);
          r2d->drawLine(rx, ty, rx, tcy, lw);
          r2d->drawLine(lx, tcy, mx, my, lw);
          r2d->drawLine(rx, tcy, mx, my, lw);
          r2d->drawLine(mx, my, mx, by, lw);
          break;

        case 'Z':
          r2d->drawLine(lx, ty, rx, ty, lw);
          r2d->drawLine(rx, ty, lx, by, lw);
          r2d->drawLine(lx, by, rx, by, lw);
          break;
      }
    };

    private:
    Render2d * r2d;
  };
}
