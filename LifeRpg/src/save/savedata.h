#pragma once
#include "math/geometry/point3d.h"
#include "app/iscene.h"

typedef struct SaveData {
  fin::app::IScene* scene_;
  fin::math::Point3d position_;
} SaveData;
