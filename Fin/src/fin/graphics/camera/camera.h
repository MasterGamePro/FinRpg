#pragma once

#include "fin/app/stage.h"
#include "fin/math/geometry/normal3d.h"
#include "fin/math/geometry/point3d.h"

namespace fin::graphics {
  class IGraphics;
  class View;

  enum ProjectionType {
    PROJECTION_ORTHO,
    PROJECTION_PERSPECTIVE
  };

  class Camera {
    friend app::IApp;

  public:
    Camera() {}
    void render(IGraphics* g) const;
    void set_stage(app::Stage* stage) { this->stage = stage; }

    void set_field_of_view(double fieldOfView) { this->fieldOfView = fieldOfView; }
    math::Point3d& get_from_point() { return fromPoint; }
    math::Point3d& get_to_point() { return toPoint; }
    math::Normal3d get_normal() const { return toPoint - fromPoint; }

  private:
    ProjectionType projectionType = PROJECTION_PERSPECTIVE;
    app::Stage* stage;
    double fieldOfView = 45;
    math::Point3d fromPoint, toPoint;
  };
}
