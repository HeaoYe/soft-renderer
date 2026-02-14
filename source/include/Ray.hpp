
#pragma once

#include "Vector.hpp"

class Ray {
public:
  Ray() = default;
  Ray(Vec3 orig, Vec3 dir) : orig_(orig), dir_(dir) {}

  Vec3 at(double t) { return orig_ + t * dir_; }

  Vec3 orig_;
  Vec3 dir_;
};
