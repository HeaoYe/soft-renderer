
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

template <typename typeT, size_t sizeT> class Buffer {
public:
  virtual ~Buffer() = default;
  std::array<typeT, sizeT> data_;
  auto getData() { return data_.data(); }
  auto getSize() { return data_.size(); }
  auto &operator[](size_t i) { return data_[i]; }
};

template <size_t imageWidthT, size_t imageHeightT>
class RGBBuffer final : public Buffer<uint8_t, 3 * imageWidthT * imageHeightT> {
};

class Tile final {
public:
  Tile(size_t fromX, size_t fromY, size_t width, size_t height, size_t spp)
      : fromX_(fromX), fromY_(fromY), width_(width), height_(height),
        spp_(spp) {}
  void renderTile() {
    // Implement the rendering logic for the tile here
  }

private:
  size_t fromX_, fromY_, width_, height_;
  size_t spp_;
};
