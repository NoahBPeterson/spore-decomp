#include "resource/DBPF.h"

#include <cstring>

#include "resource/RefPack.h"

namespace Spore::Resource {
namespace {

constexpr size_t kHeaderSize = 0x60;

uint32_t LE32(const uint8_t* p) {
  return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
uint16_t LE16(const uint8_t* p) { return uint16_t(p[0] | p[1] << 8); }

}  // namespace

bool DatabasePackedFile::Open(const std::string& path) {
  entries_.clear();
  file_.close();
  file_.open(path, std::ios::binary);
  if (!file_) return Fail("cannot open " + path);
  file_.seekg(0, std::ios::end);
  fileSize_ = static_cast<uint64_t>(file_.tellg());
  file_.seekg(0);

  uint8_t hdr[kHeaderSize];
  if (fileSize_ < kHeaderSize || !file_.read(reinterpret_cast<char*>(hdr), kHeaderSize))
    return Fail("truncated header");
  if (std::memcmp(hdr, "DBPF", 4) != 0) return Fail("bad magic");
  major_ = LE32(hdr + 0x04);
  minor_ = LE32(hdr + 0x08);
  if (major_ != 2 && major_ != 3) return Fail("unsupported DBPF version");

  const uint32_t count = LE32(hdr + 0x24);
  const uint32_t indexSize = LE32(hdr + 0x2C);
  const uint32_t indexOffset = LE32(hdr + 0x40);
  if (uint64_t(indexOffset) + indexSize > fileSize_) return Fail("index out of range");

  std::vector<uint8_t> idx(indexSize);
  file_.seekg(indexOffset);
  if (!file_.read(reinterpret_cast<char*>(idx.data()), indexSize)) return Fail("index read");

  size_t p = 0;
  auto need = [&](size_t n) { return p + n <= idx.size(); };
  if (!need(4)) return Fail("index too small");
  const uint32_t flags = LE32(&idx[p]);
  p += 4;
  // Bits 0..2 mark type / group / unknown as constant for every entry.
  uint32_t constant[3] = {};
  for (int i = 0; i < 3; ++i) {
    if (flags & (1u << i)) {
      if (!need(4)) return Fail("index too small");
      constant[i] = LE32(&idx[p]);
      p += 4;
    }
  }

  entries_.reserve(count);
  for (uint32_t n = 0; n < count; ++n) {
    IndexEntry e;
    uint32_t vary[3];
    for (int i = 0; i < 3; ++i) {
      if (flags & (1u << i)) {
        vary[i] = constant[i];
      } else {
        if (!need(4)) return Fail("index entry truncated");
        vary[i] = LE32(&idx[p]);
        p += 4;
      }
    }
    if (!need(20)) return Fail("index entry truncated");
    e.key.type = vary[0];
    e.key.group = vary[1];
    e.unknown = vary[2];
    e.key.instance = LE32(&idx[p]);
    e.offset = LE32(&idx[p + 4]);
    e.diskSize = LE32(&idx[p + 8]) & 0x7FFFFFFFu;
    e.memSize = LE32(&idx[p + 12]);
    e.compressed = LE16(&idx[p + 16]) == 0xFFFF;
    e.committed = LE16(&idx[p + 18]);
    p += 20;
    if (uint64_t(e.offset) + e.diskSize > fileSize_) return Fail("entry out of range");
    entries_.push_back(e);
  }
  return true;
}

const IndexEntry* DatabasePackedFile::Find(const ResourceKey& key) const {
  for (const auto& e : entries_)
    if (e.key == key) return &e;
  return nullptr;
}

std::optional<std::vector<uint8_t>> DatabasePackedFile::ReadRaw(const IndexEntry& e) {
  std::vector<uint8_t> buf(e.diskSize);
  file_.clear();
  file_.seekg(e.offset);
  if (!file_.read(reinterpret_cast<char*>(buf.data()), e.diskSize)) return std::nullopt;
  return buf;
}

std::optional<std::vector<uint8_t>> DatabasePackedFile::Read(const IndexEntry& e) {
  auto raw = ReadRaw(e);
  if (!raw || !e.compressed) return raw;
  auto out = RefPackDecompress(raw->data(), raw->size());
  if (!out || out->size() != e.memSize) return std::nullopt;
  return out;
}

}  // namespace Spore::Resource
