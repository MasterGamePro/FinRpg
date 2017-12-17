#pragma once
#include <stdio.h>
#include <direct.h>
#include "fin/algorithm/string/format.h"
#include "fin/app/actor/iactor.h"
#include "fin/debug/memory.h"
#include "fin/graphics/texture/imagetexture.h"
#include "fin/input/iinput.h"
#include "fin/math/trig.h"
#include "fin/time/deltatime.h"

class ICharacter : public fin::app::IActor {
public:
  ICharacter(std::string name, fin::graphics::ITextures* ts) {
    fin::debug::totalBytes -= sizeof(fin::app::IActor);
    fin::debug::totalBytes += sizeof(ICharacter);

    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);

    std::string folderPath = "resources/characters/" + name + "/";
    standingTextures.push_back(ts->load_texture(fin::io::File(folderPath + "standing-0.png")));

    for (int i = 0; i < 4; i++) {
      std::string path = fin::algorithm::string_format("%swalking-%d.png", folderPath.c_str(), i);
      fin::debug::Log::println(path);
      walkingTextures.push_back(ts->load_texture(fin::io::File(path)));
    }
  }

  ~ICharacter() {
    fin::debug::totalBytes -= sizeof(ICharacter);
  }

protected:
  void on_tick_physics() override final {

  }

  void on_tick_collision() override final {

  }

  void on_tick_animation() override {
    double camDirection = 90;

    double angleError = 20;
    double angleDiff = fin::math::Trig::angle_diff(camDirection, dir);
    double absAngleDiff = fabs(angleDiff);
    if (absAngleDiff > angleError && absAngleDiff < 180 - angleError) {
      targetFlipDirection = 90 + (angleDiff > 0 ? 1 : -1) * 90;
    }

    double flipSpeed = fin::time::DeltaTime::adjust_velocity(20);
    double angleDist = fin::math::Trig::angle_dist(flipDirection, targetFlipDirection);

    if (fabs(angleDist) <= flipSpeed) {
      flipDirection = targetFlipDirection;
    }
    else {
      flipDirection += (angleDist > 0 ? 1 : -1) * flipSpeed;
    }
  }

  void on_tick_audio() override final {

  }

  void on_tick_render_ortho(fin::graphics::IGraphics* g) override {}

  void on_tick_render_perspective(fin::graphics::IGraphics* g) override final {
    fin::graphics::ITransform* t = g->t();
    t->identity();
    t->translate(x, y, z);
    t->rotate_z(flipDirection);

    g->p()->color3d(1, 1, 1);
    g->r3d()->draw_floor(-8, -8, 8, 8, 0);

    index += .1;
    fin::graphics::ImageTexture* img = walkingTextures[(int) index % 4];

    int xd = -2;

    g->ts()->bind(img);
    g->r3d()->draw_wall(xd - 8, 0, 16, xd + 8, 0, 0);
    g->ts()->bind(nullptr);
  }

protected:
  double x = 0, y = 0, z = 0, s = 16;
  double vX = 0, vY = 0;
  double dir = 0;
  double index = 0;

private:
  double flipDirection = 0, targetFlipDirection = 0;
  fin::data::StlVector<fin::graphics::ImageTexture*> standingTextures;
  fin::data::StlVector<fin::graphics::ImageTexture*> walkingTextures;
};
