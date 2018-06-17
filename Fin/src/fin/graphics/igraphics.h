#pragma once

#include "fin/app/iservice.h"
#include "render2d.h"
#include "render3d.h"
#include "itransform.h"
#include "iscreen.h"
#include "itextures.h"
#include "rendervectortext.h"

namespace fin::graphics {
  class IGraphics : public app::IService {
    public:
    IGraphics(IPrimitives* _p, ITransform* _t, IScreen* _s) {
      this->_p = _p;
      this->_t = _t;
      this->_s = _s;
      _r2d = new Render2d(_p);
      _r3d = new Render3d(_p);
      //_rt = new RenderVectorText(_r2d);
    }

    virtual ~IGraphics() {}

    void init() override {
      on_init();
    }

    IPrimitives* p() const { return _p; }
    ITransform* t() const { return _t; }
    IScreen* s() const { return _s; }
    virtual ITextures* ts() const = 0;

    Render2d* r2d() const { return _r2d; }
    Render3d* r3d() const { return _r3d; }
    virtual IRenderText* rt() const = 0;

    private:
    virtual void on_init() = 0;

    IPrimitives* _p;
    ITransform* _t;
    IScreen* _s;
    Render2d* _r2d;
    Render3d* _r3d;
  };
}
