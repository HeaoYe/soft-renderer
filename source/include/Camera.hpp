
#pragma once

#include "Ray.hpp"
#include "Vector.hpp"
#include <cstddef>

// NOTE: using right-hand coordinate

class Camera {
public:
  Camera(Vec3 orig, double viewPortWidth, double viewPortHeight,
         size_t imageWidth, size_t imageHeight, double focalLength, Vec3 up,
         Vec3 lookAt, size_t maxDepth_)
      : orig_(orig), u((viewPortWidth / imageWidth) *
                       cross(normalize(lookAt), normalize(up))),
        v(-(viewPortHeight / imageHeight) * normalize(up)),
        higherLeftCorner(
            focalLength * normalize(lookAt) +
            0.5 * viewPortWidth * cross(normalize(up), normalize(lookAt)) +
            0.5 * normalize(up) * viewPortHeight + 0.5 * u + 0.5 * v),
        maxDepth_(maxDepth_) {}

  Ray getRay(size_t x, size_t y) {
    return {orig_, higherLeftCorner + static_cast<double>(x) * u +
                       static_cast<double>(y) * v};
  }
  Vec3 orig_;
  Vec3 u, v;
  Vec3 higherLeftCorner;
  size_t maxDepth_;
};
