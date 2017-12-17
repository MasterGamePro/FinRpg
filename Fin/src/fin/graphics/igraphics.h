#pragma once

#include "fin/app/iservice.h"
#include "render2d.h"
#include "render3d.h"
#include "rendervectortext.h"
#include "itransform.h"
#include "iscreen.h"

namespace fin::graphics {
  class IGraphics : public app::IService {
  public:
    IGraphics(IPrimitives* _p, ITransform* _t, IScreen* _s) {
      this->_p = _p;
      this->_t = _t;
      this->_s = _s;
      _r2d = new Render2d(_p);
      _r3d = new Render3d(_p);
      _rt = new RenderVectorText(_r2d);
    }

    IScreen* s() const { return _s; }
    IPrimitives* p() const { return _p; }

    Render2d* r2d() const { return _r2d; }
    Render3d* r3d() const { return _r3d; }

    IRenderText* rt() const { return _rt; }
    ITransform* t() const { return _t; }

  private:
    IScreen * _s;
    IPrimitives* _p;
    Render2d* _r2d;
    Render3d* _r3d;
    IRenderText* _rt;
    ITransform* _t;
  };
}
