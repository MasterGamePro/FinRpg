#pragma once

#include "fin/app/iservice.h"
#include "render2d.h"
#include "render3d.h"
#include "itransform.h"
#include "iscreen.h"
#include "itextures.h"
#include "renderfonttext.h"
#include "rendervectortext.h"

namespace fin::graphics {
  class IGraphics : public app::IService {
    public:
    IGraphics(IPrimitives* _p, ITransform* _t, IScreen* _s, ITextures* _ts) {
      this->_p = _p;
      this->_t = _t;
      this->_s = _s;
      this->_ts = _ts;
      _r2d = new Render2d(_p);
      _r3d = new Render3d(_p);
      //_rt = new RenderVectorText(_r2d);
      _rt = new RenderFontText(_p, _ts);
    }
    virtual ~IGraphics() {}

    void init() override {
      _rt->init();
    }

    IPrimitives* p() const { return _p; }
    ITransform* t() const { return _t; }
    IScreen* s() const { return _s; }
    ITextures* ts() const { return _ts; }

    Render2d* r2d() const { return _r2d; }
    Render3d* r3d() const { return _r3d; }
    IRenderText* rt() const { return _rt; }

    private:
    IPrimitives * _p;
    ITransform* _t;
    IScreen * _s;
    ITextures* _ts;
    Render2d* _r2d;
    Render3d* _r3d;
    IRenderText* _rt;
  };
}
