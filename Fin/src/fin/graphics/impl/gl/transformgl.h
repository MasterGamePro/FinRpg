#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include "fin/graphics/itransform.h"
#include "fin/math/geometry/inormal3d.h"

namespace fin::graphics {
  class TransformGl : public ITransform {
    void set_target_matrix(MatrixType matrixType) override final {
      this->matrixType = matrixType;
      switch (matrixType) {
        case MatrixType::MODELVIEW:
          glMatrixMode(GL_MODELVIEW);
          break;
        case MatrixType::PROJECTION:
          glMatrixMode(GL_PROJECTION);
          break;
      }
    }

    void print_matrix() override final {
      float v[16];
      glGetFloatv(matrixType == MatrixType::MODELVIEW
                    ? GL_MODELVIEW_MATRIX
                    : GL_PROJECTION_MATRIX, v);
      for (int y = 0; y < 4; y++) {
        std::string str = "";
        for (int x = 0; x < 4; x++) {
          str += algorithm::format_string("%5.2lf ", v[y*4 + x]);
        }
        debug::Log::println(str);
      }
    }

    void push_matrix() override final { glPushMatrix(); }
    void pop_matrix() override final { glPopMatrix(); }

    void identity() override final { glLoadIdentity(); }

    void translate(const double x, const double y) override final {
      translate(x, y, 0);
    }

    void translate(const double x, const double y, const double z) override
    final { glTranslated(x, y, z); }

    void scale(const double x, const double y) override final {
      scale(x, y, 1);
    }
    void scale(const double x, const double y, const double z) override final {
      glScaled(x, y, z);
    }

    void rotate_x(const double deg) override final { glRotated(deg, 1, 0, 0); }
    void rotate_y(const double deg) override final { glRotated(deg, 0, 1, 0); }
    void rotate_z(const double deg) override final { glRotated(deg, 0, 0, 1); }

    void rotate_around_axis(const math::INormal3d& axis, const double deg)
    override final { glRotated(deg, axis.x(), axis.y(), axis.z()); }

    void perspective(double fov, double aspect, double nearValue,
                     double farValue) override final {
      gluPerspective(fov, aspect, nearValue, farValue);
    }

    void ortho(double left, double right, double bottom, double top,
               double nearValue, double farValue) {
      glOrtho(left, right, bottom, top, nearValue, farValue);
    }

    void look_at(const math::Point3d& from, const math::Point3d& to,
                 const math::INormal3d& up) {
      gluLookAt(from.x(), from.y(), from.z(), to.x(), to.y(), to.z(), up.x(),
                up.y(), up.z());
    }

    private:
    MatrixType matrixType;
  };
}
