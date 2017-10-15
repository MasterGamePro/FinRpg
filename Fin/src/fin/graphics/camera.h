#pragma once

#include "fin/app/stage.h"

namespace fin::graphics {
  class IGraphics;
  class View;

  enum ProjectionType {
    PROJECTION_ORTHO,
    PROJECTION_PERSPECTIVE
  };

  class Camera {
    public:

    void render( IGraphics* g ) const;
    void set_stage( app::Stage* stage ) { this->stage = stage; }
    void set_field_of_view( double fieldOfView ) { this->fieldOfView = fieldOfView; }

    private:
    ProjectionType projectionType = PROJECTION_ORTHO;
    app::Stage* stage;
    double fieldOfView;
  };
}
