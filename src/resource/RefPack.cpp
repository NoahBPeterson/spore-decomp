#include "resource/RefPack.h"

namespace Spore::Resource {
namespace {

struct Header {
  uint32_t outSize;
  size_t length;
};

std::optional<Header> ParseHeader(const uint8_t* s, size_t n) {
  if (n < 2 || s[1] != 0xFB) return std::nullopt;
  const uint8_t flags = s[0];
  const size_t field = (flags & 0x80) ? 4 : 3;
  size_t pos = 2;
  if (flags & 0x01) pos += field;  // optional compressed-size field
  if (n < pos + field) return std::nullopt;
  uint32_t size = 0;
  for (size_t i = 0; i < field; ++i) size = (size << 8) | s[pos + i];
  return Header{size, pos + field};
}

}  // namespace

std::optional<uint32_t> RefPackDecompressedSize(const uint8_t* src, size_t srcSize) {
  auto h = ParseHeader(src, srcSize);
  if (!h) return std::nullopt;
  return h->outSize;
}

std::optional<std::vector<uint8_t>> RefPackDecompress(const uint8_t* src, size_t srcSize) {
  auto h = ParseHeader(src, srcSize);
  if (!h) return std::nullopt;
  std::vector<uint8_t> out;
  out.reserve(h->outSize);
  size_t in = h->length;

  for (;;) {
    if (in >= srcSize) return std::nullopt;
    const uint8_t b0 = src[in];
    size_t plain = 0, copy = 0, offset = 0;
    bool stop = false;

    if (b0 < 0x80) {
      if (in + 2 > srcSize) return std::nullopt;
      const uint8_t b1 = src[in + 1];
      in += 2;
      plain = b0 & 0x03;
      copy = ((b0 & 0x1C) >> 2) + 3;
      offset = ((b0 & 0x60) << 3) + b1 + 1;
    } else if (b0 < 0xC0) {
      if (in + 3 > srcSize) return std::nullopt;
      const uint8_t b1 = src[in + 1], b2 = src[in + 2];
      in += 3;
      plain = (b1 >> 6) & 0x03;
      copy = (b0 & 0x3F) + 4;
      offset = ((b1 & 0x3F) << 8) + b2 + 1;
    } else if (b0 < 0xE0) {
      if (in + 4 > srcSize) return std::nullopt;
      const uint8_t b1 = src[in + 1], b2 = src[in + 2], b3 = src[in + 3];
      in += 4;
      plain = b0 & 0x03;
      copy = ((b0 & 0x0C) << 6) + b3 + 5;
      offset = ((b0 & 0x10) << 12) + (b1 << 8) + b2 + 1;
    } else if (b0 < 0xFC) {
      in += 1;
      plain = ((b0 & 0x1F) << 2) + 4;
    } else {
      in += 1;
      plain = b0 & 0x03;
      stop = true;
    }

    if (in + plain > srcSize) return std::nullopt;
    out.insert(out.end(), src + in, src + in + plain);
    in += plain;

    if (copy) {
      if (offset > out.size()) return std::nullopt;
      size_t from = out.size() - offset;
      for (size_t i = 0; i < copy; ++i) out.push_back(out[from + i]);  // may overlap
    }
    if (stop) break;
  }
  if (out.size() != h->outSize) return std::nullopt;
  return out;
}

}  // namespace Spore::Resource
