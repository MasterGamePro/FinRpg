#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include "fin/graphics/itransform.h"
#include "fin/math/geometry/inormal3d.h"

namespace fin::graphics {
  class TransformGl : public ITransform {
    void set_target_matrix(MatrixType matrixType) override final {
      switch (matrixType) {
      case MATRIX_MODELVIEW:
        glMatrixMode(GL_MODELVIEW);
        break;
      case MATRIX_PROJECTION:
        glMatrixMode(GL_PROJECTION);
        break;
      }
    }

    void push_matrix() override final { glPushMatrix(); }
    void pop_matrix() override final { glPopMatrix(); }

    void identity() override final { glLoadIdentity(); }

    void translate(double x, double y) override final { translate(x, y, 0); }
    void translate(double x, double y, double z) override final { glTranslated(x, y, z); }

    void scale(double x, double y) override final { scale(x, y, 1); }
    void scale(double x, double y, double z) override final { glScaled(x, y, z); }

    void rotate_x(double deg) override final { glRotated(deg, 1, 0, 0); }
    void rotate_y(double deg) override final { glRotated(deg, 0, 1, 0); }
    void rotate_z(double deg) override final { glRotated(deg, 0, 0, 1); }

    void perspective(double fov, double aspect, double nearValue, double farValue) override final {
      gluPerspective(fov, aspect, nearValue, farValue);
    }
    void ortho(double left, double right, double bottom, double top, double nearValue, double farValue) {
      glOrtho(left, right, bottom, top, nearValue, farValue);
    }
    void look_at(const math::Point3d& from, const math::Point3d& to, const math::INormal3d& up) {
      gluLookAt(from.x(), from.y(), from.z(), to.x(), to.y(), to.z(), up.x(), up.y(), up.z());
    }
  };
}
