
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
class ImageBuffer final
    : public Buffer<uint8_t, 3 * imageWidthT * imageHeightT> {};
