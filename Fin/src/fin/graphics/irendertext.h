#pragma once

#include "render2d.h"
#include <string>
#include <cctype>
#include "fin/time/time.h"
#include "fin/math/Random.h"
#include "fin/math/trig.h"

namespace fin::graphics {

  enum TextAnimationType {
    TEXTANIMATION_NONE,
    TEXTANIMATION_WAVE,
    TEXTANIMATION_SHAKE,
    TEXTANIMATION_JIGGLE
  };

  class IRenderText {
    public:
    IRenderText( Render2d* r2d ) {
      this->r2d = r2d;
    }

    // TODO: Make this private?
    virtual void draw_char( char c, double x, double y, double w, double h ) const = 0;

    // TODO: Switch order of x, y & string, and add format params.
    void draw_string( const std::string& str, double x, double y ) const {
      double x0 = x, cW = 8, cH = 12, cPX = cW * .2;
      const auto tf = time::Time::mod_ms( 1000 );

      for ( int i = 0, len = str.length(); i < len; i++ ) {
        const auto c = str.at( i );

        double w, h;
        if ( isupper( c ) ) {
          w = cW;
          h = cH;
        } else {
          w = .6*cW;
          h = .6*cH;
        }

        double dx, dy;
        switch ( textAnimationType ) {
          case TEXTANIMATION_WAVE:
            dx = x + cW / 4 * cos( math::Trig::kTau*tf + i*.5 );
            dy = y + cH / 4 * sin( math::Trig::kTau*tf + i*.5 );
            break;

          case TEXTANIMATION_SHAKE:
            dx = x + cW / 8 * math::Random::randomd( -1, 1 );
            dy = y + cH / 8 * math::Random::randomd( -1, 1 );
            break;

          case TEXTANIMATION_JIGGLE:
            dx = x;
            dy = y +cH / 16 * sin( math::Trig::kTau*tf + i*.5 );
            break;

          case TEXTANIMATION_NONE:
          default:
            dx = x;
            dy = y;
            break;
        }

        draw_char( c, dx, dy + cH - h, w, h );
        x += w + cPX;
      }
    }

    protected:
    TextAnimationType textAnimationType = TEXTANIMATION_JIGGLE; // TEXTANIMATION_SHAKE;
    Render2d* r2d;
  };
}
