
#include "Camera.hpp"
#include "Hittable.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

inline Ray getRay(Camera &cam, size_t x, size_t y) {
  return Ray{cam.orig_, cam.higherLeftCorner + static_cast<double>(x) * cam.u +
                            static_cast<double>(y) * cam.v};
}

uint8_t toByte(double col) {
  return int(col * 255.999);
}

HittableList world;

Vec3 rayColor(size_t depth, Ray r, Vec3 attenuation) {

  if (depth == 1000)
    return {1, 0, 1};
  depth++;

  Ray scattered;
  HitInfo hitInf{};
  bool hit = world.hit(r, 0.0001, std::numeric_limits<double>::max(), hitInf);
  if (hit) {
    if (hitInf.mat->scatter(r, hitInf, attenuation, scattered))
      return attenuation * rayColor(depth, scattered, attenuation);
  } else {
    auto a = 0.5 * (normalize(r.dir_).y + 1);
    Vec3 up{0.5, 0.7, 1.0};
    Vec3 down{1, 1, 1.0};
    return a * down + (1 - a) * up;
    return {1, 1, 1};
  }
  return {1, 0, 0};
}

// constants
constexpr size_t IMAGE_WIDTH{1920};
constexpr size_t IMAGE_HEIGHT{1080};
constexpr size_t SPP{31};

int main(int argc, char *argv[]) {

  std::ofstream Imagefile("Image.ppm", std::ios::binary);
  Imagefile << "P6\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

  // camera
  Camera cam(Vec3{0, -5, -30}, 1.6, 0.9, IMAGE_WIDTH, IMAGE_HEIGHT, 0.8,
             Vec3{0, -1, 0}, Vec3{0, 0, 1}, 100);

  world.add(std::make_shared<Sphere>(
      Vec3{
          0,
          -5.0001,
          0,
      },
      5, std::make_shared<Lambert>()));

  world.add(std::make_shared<Sphere>(
      Vec3{
          10.1,
          -5.0001,
          0,
      },
      5, std::make_shared<Metal>()));

  world.add(std::make_shared<Sphere>(
      Vec3{
          3,
          -6.0001,
          -10.0001,
      },
      6, std::make_shared<Dielectric>()));

  world.add(std::make_shared<Plane>(Vec3{0, 0, 0}, Vec3{0, -1, 0},
                                    std::make_shared<Lambert>()));

  // for loops
  std::vector<uint8_t> buffer(3 * IMAGE_WIDTH * IMAGE_HEIGHT);
  for (size_t y{0}; y != IMAGE_HEIGHT; y++) {
    std::clog << "\r" << y;
    for (size_t x{0}; x != IMAGE_WIDTH; x++) {
      Vec3 attenuation{1, 1, 1};
      Vec3 color = rayColor(0, cam.getRay(x, y), attenuation);
      size_t index = y * IMAGE_WIDTH + x;
      buffer[index + 0] = toByte(color.r);
      buffer[index + 1] = toByte(color.g);
      buffer[index + 2] = toByte(color.b);
    }
  }
  Imagefile.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());

  Imagefile.close();
  return 0;
}
