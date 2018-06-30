#pragma once
#include <direct.h>
#include <stdio.h>
#include "fin/algorithm/string/format.h"
#include "fin/app/actor/iactor.h"
#include "fin/app/components/data/positiondata3d.h"
#include "fin/graphics/texture.h"
#include "fin/input/iinput.h"
#include "fin/math/geometry/common.h"
#include "fin/math/trig.h"
#include "fin/time/deltatime.h"

// TODO: Depth-sort in DepthManager LifeRpg class.
class ICharacter : public fin::app::IActor {
  public:
  ICharacter(std::string name, fin::graphics::ITextures* ts) {
    positionData_ = std::make_shared<fin::app::PositionData3d>();

    char buffer[FILENAME_MAX];
    _getcwd(buffer, FILENAME_MAX);

    std::string folderPath = "resources/characters/" + name + "/";
    standingTextures.
      push_back(ts->load_texture(fin::io::File(folderPath + "standing-0.png")));

    for (int i = 0; i < 4; i++) {
      std::string path = fin::algorithm::format_string("%swalking-%d.png",
                                                       folderPath.c_str(), i);
      fin::debug::Log::println(path);
      walkingTextures.push_back(ts->load_texture(fin::io::File(path)));
    }

    shadowTexture = ts->
      load_texture(fin::io::File("resources/images/shadow.png"));
  }

  protected:
  void move(double amount, double dir) {
    moveAmt = amount;
    if (amount > 0) {
      this->dir_ = dir;
      isMoving = true;
      positionData_->v_x(amount * fin::math::cosd(dir));
      positionData_->v_y(amount * fin::math::sind(dir));
    }
    else {
      isMoving = false;
      positionData_->v_x(0);
      positionData_->v_y(0);
    }
  }

  bool move_towards(const double x, const double y, const double amount) {
    const auto x_ = positionData_->p_x();
    const auto y_ = positionData_->p_y();
    const auto dis = fin::math::calc_pt_dis(x_, y_, x, y);
    const auto dir = fin::math::calc_pt_dir_d(x_, y_, x, y);

    if (dis > 0) {
      dir_ = dir;
      if (dis <= amount) {
        moveAmt = 0;
        positionData_->p_x(x);
        positionData_->p_y(y);
        positionData_->v_x(0);
        positionData_->v_y(0);
        isMoving = false;
        return true;
      }
      moveAmt = amount;
      // TODO: Add forces? Or "velocity" forces?
      positionData_->v_x(amount * fin::math::cosd(dir));
      positionData_->v_y(amount * fin::math::sind(dir));
      isMoving = true;
    }
    return false;
  }

  void on_tick_physics() override { positionData_->tick(); }

  void on_tick_collision() override { }

  void on_tick_animation() override {
    // TODO: Rotate based on the trajectory of the angular velocity.
    double camDirection = -90;

    double angleError = 20;
    double angleDiff = fin::math::angle_diffd(camDirection, dir_);

    double absAngleDiff = fabs(angleDiff);
    if (absAngleDiff > angleError && absAngleDiff < 180 - angleError) {
      targetFlipDirection = 90 + (angleDiff > 0 ? 1 : -1) * 90;
    }

    double flipSpeed = fin::time::DeltaTime::adjust_velocity(20);
    double angleDist = fin::math::angle_distd(flipDirection,
                                              targetFlipDirection);

    if (fabs(angleDist) <= flipSpeed) { flipDirection = targetFlipDirection; }
    else { flipDirection += (angleDist > 0 ? 1 : -1) * flipSpeed; }
  }

  void on_tick_audio() override { }

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override {}

  void on_tick_render_perspective(fin::graphics::IGraphics* g) override {
    g->r3d()->draw_floor(-500, -500, 500, 500, -1);

    fin::graphics::ITransform* t = g->t();
    t->identity();
    t->translate(positionData_->p_xyz());
    t->rotate_z(flipDirection);

    g->p()->color3d(1, 1, 1);

    g->ts()->bind(shadowTexture);
    g->r3d()->draw_floor(-5, -1, 5, 1, 0);

    fin::graphics::Texture img;

    if (isMoving) {
      index += moveAmt * .15;
      img = walkingTextures[(int)index % 4];
    }
    else { img = standingTextures[0]; }

    int xd = -2;

    g->ts()->bind(img);
    g->r3d()->draw_wall(xd - 8, 0, 16, xd + 8, 0, 0);
    g->ts()->unbind();
  }

  protected:
  bool isMoving = false;
  double moveAmt = 0;
  double s = 16;

  // TODO: Make PositionActor.
  std::shared_ptr<fin::app::PositionData3d> positionData_;
  double dir_ = 0;
  double index = 0;

  private:
  double flipDirection = 0, targetFlipDirection = 0;
  fin::data::StlVector<fin::graphics::Texture> standingTextures;
  fin::data::StlVector<fin::graphics::Texture> walkingTextures;
  fin::graphics::Texture shadowTexture;
};
