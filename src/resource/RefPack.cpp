#include "resource/RefPack.h"

namespace Spore::Resource {

uint32_t RefPackReadBE(const uint8_t* p, int count) {
  switch (count) {
    case 1: return p[0];
    case 2: return uint32_t(p[0]) << 8 | p[1];
    case 3: return uint32_t(p[0]) << 16 | uint32_t(p[1]) << 8 | p[2];
    case 4: return uint32_t(p[0]) << 24 | uint32_t(p[1]) << 16 | uint32_t(p[2]) << 8 | p[3];
    default: return 0;
  }
}

bool RefPackIsValidHeader(const uint8_t* src, size_t srcSize) {
  return srcSize >= 2 && ((uint32_t(src[0]) << 8 | src[1]) & 0x1FFF) == 0x10FB;
}

std::optional<uint32_t> RefPackDecompressedSize(const uint8_t* src, size_t srcSize) {
  if (!RefPackIsValidHeader(src, srcSize)) return std::nullopt;
  const int n = (src[0] & 0x80) ? 4 : 3;
  if (srcSize < size_t(2 + n)) return std::nullopt;
  return RefPackReadBE(src + 2, n);
}

std::optional<std::vector<uint8_t>> RefPackDecompress(const uint8_t* src, size_t srcSize) {
  auto declared = RefPackDecompressedSize(src, srcSize);
  if (!declared) return std::nullopt;

  // Header layout as walked by 0x0092C340 (the 0x01 skip is dead code after
  // RefPackIsValidHeader, but kept to mirror the original).
  size_t in = 2;
  if (src[0] & 0x80) {
    if (src[0] & 0x01) in += 4;
    in += 4;
  } else {
    if (src[0] & 0x01) in += 3;
    in += 3;
  }

  std::vector<uint8_t> out;
  out.reserve(*declared);
  auto literals = [&](size_t n) {
    if (in + n > srcSize || out.size() + n > *declared) return false;
    out.insert(out.end(), src + in, src + in + n);
    in += n;
    return true;
  };
  auto backref = [&](size_t distance, size_t n) {
    if (distance > out.size() || out.size() + n > *declared) return false;
    size_t from = out.size() - distance;
    for (size_t i = 0; i < n; ++i) out.push_back(out[from + i]);  // may overlap
    return true;
  };

  for (;;) {
    if (in >= srcSize) return std::nullopt;
    const uint8_t b0 = src[in];
    if (b0 < 0x80) {  // 2-byte: 0..3 literals, copy 3..10, distance <= 1024
      if (in + 2 > srcSize) return std::nullopt;
      const uint8_t b1 = src[in + 1];
      in += 2;
      if (!literals(b0 & 3) || !backref(((b0 & 0x60) << 3) + b1 + 1, ((b0 >> 2) & 7) + 3))
        return std::nullopt;
    } else if (b0 < 0xC0) {  // 3-byte: copy 4..67, distance <= 16384
      if (in + 3 > srcSize) return std::nullopt;
      const uint8_t b1 = src[in + 1], b2 = src[in + 2];
      in += 3;
      if (!literals(b1 >> 6) || !backref(((b1 & 0x3F) << 8) + b2 + 1, (b0 & 0x3F) + 4))
        return std::nullopt;
    } else if (b0 < 0xE0) {  // 4-byte: copy 5..1028, distance <= 131072
      if (in + 4 > srcSize) return std::nullopt;
      const uint8_t b1 = src[in + 1], b2 = src[in + 2], b3 = src[in + 3];
      in += 4;
      if (!literals(b0 & 3) ||
          !backref(((b0 & 0x10) << 12) + (b1 << 8) + b2 + 1, ((b0 & 0x0C) << 6) + b3 + 5))
        return std::nullopt;
    } else {
      in += 1;
      const size_t n = ((b0 & 0x1F) << 2) + 4;
      if (n <= 0x70) {  // 4..112 literals
        if (!literals(n)) return std::nullopt;
      } else {  // 0xFC..0xFF: 0..3 trailing literals, end of stream
        if (!literals(b0 & 3)) return std::nullopt;
        break;
      }
    }
  }
  // The original returns the declared size regardless of bytes written; callers
  // (0x008D8820) then require declared == index memSize. We require an exact fill.
  if (out.size() != *declared) return std::nullopt;
  return out;
}

}  // namespace Spore::Resource
