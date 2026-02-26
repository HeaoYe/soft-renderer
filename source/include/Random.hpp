#pragma once

#include "Vector.hpp"
#include <random>

inline double randomDouble(std::mt19937_64 &rng, double min, double max) {
  std::uniform_real_distribution<double> dist(min, max);
  return dist(rng);
}

inline Vec3 sphericalRand(std::mt19937_64 &rng) {
  // radius is set to 1.0 by default, but can be changed by multiplying the
  // result by the desired radius double theta =
  double theta = randomDouble(rng, 0, 6.283185307179586476925286766559);
  double phi = std::acos(randomDouble(rng, -1, 1));

  double x = std::sin(phi) * std::cos(theta);
  double y = std::sin(phi) * std::sin(theta);
  double z = std::cos(phi);

  return Vec3(x, y, z);
}

// template <typename T>
// GLM_FUNC_QUALIFIER vec<3, T, defaultp> sphericalRand(T Radius) {
//   assert(Radius > static_cast<T>(0));
//
//   T theta = linearRand(T(0), T(6.283185307179586476925286766559f));
//   T phi = std::acos(linearRand(T(-1.0f), T(1.0f)));
//
//   T x = std::sin(phi) * std::cos(theta);
//   T y = std::sin(phi) * std::sin(theta);
//   T z = std::cos(phi);
//
//   return vec<3, T, defaultp>(x, y, z) * Radius;
// }
