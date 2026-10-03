#include "resource/DBPF.h"

#include <cstring>

#include "resource/RefPack.h"

namespace Spore::Resource {
namespace {

constexpr size_t kHeaderSize = 0x60;

// 16-byte marker preceding an embedded package. Stored in the exe with its
// first byte inverted (DAT_01436998 = 7F 9D 88 EC ...) and flipped at runtime.
constexpr uint8_t kEmbeddedMarker[16] = {0x80, 0x9D, 0x88, 0xEC, 0x8F, 0x24, 0x03, 0x6C,
                                         0xC9, 0xA6, 0x31, 0x56, 0x5B, 0xCF, 0x77, 0x20};
constexpr uint8_t kStoredMarkerPrefix[4] = {0x7F, 0x9D, 0x88, 0xEC};

uint32_t LE32(const uint8_t* p) {
  return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}

}  // namespace

bool DatabasePackedFile::VerifyHeaderRecordIntegrity(const uint8_t h[kHeaderSize],
                                                     uint64_t fileSize) {
  const uint32_t indexOffset = LE32(h + 0x40);
  const uint32_t indexOffsetHigh = LE32(h + 0x44);
  const uint32_t legacyIndexOffset = LE32(h + 0x28);
  bool valid = std::memcmp(h, "DBPF", 4) == 0 && LE32(h + 0x04) < 4 &&
               LE32(h + 0x24) < 0x7FFFFFF && indexOffset < fileSize &&
               uint32_t(LE32(h + 0x2C) + indexOffset) <= fileSize &&  // 32-bit add, as original
               LE32(h + 0x3C) != 0;
  // When both the legacy (v1) and current index offsets are present they must agree,
  // and this overrides the checks above.
  if ((indexOffset != 0 || indexOffsetHigh != 0) && legacyIndexOffset != 0)
    return indexOffset == legacyIndexOffset && indexOffsetHigh == 0;
  return valid;
}

int64_t DatabasePackedFile::FindEmbeddedHeader(std::istream& in, uint64_t fileSize) {
  // Windowed scan exactly as the original: a 0x200 buffer, refilled 0x1F1 bytes at a
  // time with a 0xF-byte overlap, searched in full (including stale tail bytes).
  uint8_t buf[0x200] = {};
  size_t carry = 0;
  uint64_t base = 0;
  bool startsWithStoredMarker = false;
  in.clear();
  in.seekg(0);
  while (base < fileSize) {
    in.read(reinterpret_cast<char*>(buf + carry), std::streamsize(sizeof buf - carry));
    const size_t got = size_t(in.gcount());
    in.clear();
    if (base == 0 && got > 3)
      startsWithStoredMarker = std::memcmp(buf, kStoredMarkerPrefix, 4) == 0;
    const uint8_t* hit = nullptr;
    for (size_t i = 0; i + sizeof kEmbeddedMarker <= sizeof buf; ++i) {
      if (std::memcmp(buf + i, kEmbeddedMarker, sizeof kEmbeddedMarker) == 0) {
        hit = buf + i;
        break;
      }
    }
    if (hit) {
      const size_t at = size_t(hit - buf);
      if (got - 0x10 < at) return -1;  // unsigned compare, as original
      return int64_t(at + 0x10 + base);
    }
    std::memmove(buf, buf + 0x1F1, 0xF);
    base += 0x1F1;
    carry = 0xF;
  }
  return startsWithStoredMarker ? 0 : -1;
}

bool DatabasePackedFile::ParseIndex(const uint8_t* data, size_t size, uint32_t count,
                                    bool committed, std::vector<IndexEntry>& out) {
  size_t p = 0;
  auto next = [&](uint32_t& v) {
    if (p + 4 > size) return false;
    v = LE32(data + p);
    p += 4;
    return true;
  };
  uint32_t flags, constType = 0xFFFFFFFF, constGroup = 0xFFFFFFFF, constThird;
  if (!next(flags)) return false;
  if (!(flags & 4)) return false;  // the third key field must be declared constant...
  if ((flags & 1) && !next(constType)) return false;
  if ((flags & 2) && !next(constGroup)) return false;
  if (!next(constThird) || constThird != 0) return false;  // ...and must be zero

  out.reserve(out.size() + count);
  for (uint32_t n = 0; n < count; ++n) {
    IndexEntry e;
    e.key.type = constType;
    e.key.group = constGroup;
    uint32_t size32;
    if (!(flags & 1) && !next(e.key.type)) return false;
    if (!(flags & 2) && !next(e.key.group)) return false;
    if (!next(e.key.instance) || !next(e.offset) || !next(size32) || !next(e.memSize))
      return false;
    if (size32 & 0x80000000u) {
      // Extended entry: an extra dword carries {u16 compression, u8 committed}.
      uint32_t extra;
      if (!next(extra)) return false;
      e.diskSize = size32 & 0x7FFFFFFFu;
      e.compression = uint16_t(extra);
      e.committed = (extra >> 16) & 1;
    } else {
      e.diskSize = size32;
      e.compression = e.diskSize == e.memSize ? 0 : 0xFFFF;
    }
    if (committed) e.committed = true;
    out.push_back(e);
  }
  return true;
}

bool DatabasePackedFile::VerifyIndexRecordIntegrity(const std::vector<IndexEntry>& entries,
                                                    uint64_t lo, uint64_t hi) {
  for (const auto& e : entries) {
    if (e.diskSize == 0) continue;
    // Absolute offsets, not header-relative, exactly as the original.
    if (uint32_t(hi - lo) <= uint32_t(e.offset - lo)) return false;
    if (uint32_t(hi - e.offset) < e.diskSize) return false;
  }
  return true;
}

bool DatabasePackedFile::ReadAt(uint64_t pos, void* dst, size_t n, size_t* got) {
  if (pos >= fileSize_) return false;
  file_.clear();
  file_.seekg(std::streamoff(pos));
  file_.read(static_cast<char*>(dst), std::streamsize(n));
  *got = size_t(file_.gcount());
  return true;  // short reads are not errors in the original
}

bool DatabasePackedFile::ReadHeaderRecord(bool allowRetry) {
  uint8_t h[kHeaderSize] = {};
  size_t got = 0;
  if (!ReadAt(headerPosition_, h, kHeaderSize, &got)) return Fail("header position out of range");
  if (got != kHeaderSize) return Fail("truncated header");
  header_.userMajor = LE32(h + 0x0C);
  header_.userMinor = LE32(h + 0x10);
  header_.createdDate = LE32(h + 0x18);
  header_.modifiedDate = LE32(h + 0x1C);
  header_.indexMajor = LE32(h + 0x20);
  header_.indexOffset = LE32(h + 0x40) ? LE32(h + 0x40) : LE32(h + 0x28);
  header_.indexCount = LE32(h + 0x24);
  header_.indexSize = LE32(h + 0x2C);
  if (VerifyHeaderRecordIntegrity(h, fileSize_)) return true;

  // Not a plain package: look for one embedded after the marker, then retry once.
  const int64_t pos = FindEmbeddedHeader(file_, fileSize_);
  if (pos < 0) {
    headerPosition_ = 0;
    return Fail("bad header");
  }
  headerPosition_ = uint32_t(pos);
  if (!allowRetry) return Fail("bad header");
  return ReadHeaderRecord(false);
}

bool DatabasePackedFile::ReadIndexRecord() {
  if (header_.indexCount == 0) return true;
  std::vector<uint8_t> buf(header_.indexSize);
  size_t got = 0;
  if (!ReadAt(uint64_t(header_.indexOffset) + headerPosition_, buf.data(), buf.size(), &got))
    return Fail("index position out of range");
  if (got == 0) return Fail("index read");
  // Deliberate divergence: the original parses past a short read; we bound to what was read.
  if (!ParseIndex(buf.data(), got, header_.indexCount, true, entries_))
    return Fail("index parse");
  if (!VerifyIndexRecordIntegrity(entries_, 0, fileSize_)) return Fail("index integrity");
  return true;
}

bool DatabasePackedFile::Open(const std::string& path) {
  entries_.clear();
  lookup_.clear();
  header_ = {};
  headerPosition_ = 0;
  file_.close();
  file_.open(path, std::ios::binary);
  if (!file_) return Fail("cannot open " + path);
  file_.seekg(0, std::ios::end);
  fileSize_ = uint64_t(file_.tellg());

  if (!ReadHeaderRecord(true) || !ReadIndexRecord()) return false;
  for (size_t i = 0; i < entries_.size(); ++i)
    lookup_.emplace(entries_[i].key, i);  // emplace keeps the first duplicate, as 0x008DB450
  return true;
}

const IndexEntry* DatabasePackedFile::Find(const ResourceKey& key) const {
  auto it = lookup_.find(key);
  return it == lookup_.end() ? nullptr : &entries_[it->second];
}

std::optional<std::vector<uint8_t>> DatabasePackedFile::ReadRaw(const IndexEntry& e) {
  std::vector<uint8_t> buf(e.diskSize);
  size_t got = 0;
  if (!ReadAt(uint64_t(headerPosition_) + e.offset, buf.data(), buf.size(), &got))
    return std::nullopt;
  buf.resize(got);
  return buf;
}

std::optional<std::vector<uint8_t>> DatabasePackedFile::Read(const IndexEntry& e) {
  auto raw = ReadRaw(e);
  if (!raw || !e.IsCompressed()) return raw;
  if (raw->empty()) return std::nullopt;
  // 0x008D8820: header must validate and declare exactly memSize bytes.
  auto declared = RefPackDecompressedSize(raw->data(), raw->size());
  if (!declared || *declared != e.memSize) return std::nullopt;
  if (*declared == 0) return std::vector<uint8_t>();
  return RefPackDecompress(raw->data(), raw->size());
}

}  // namespace Spore::Resource
