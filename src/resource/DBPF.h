#pragma once
#include <cstdint>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace Spore::Resource {

struct ResourceKey {
  uint32_t instance = 0;
  uint32_t type = 0;
  uint32_t group = 0;
  bool operator==(const ResourceKey& o) const {
    return instance == o.instance && type == o.type && group == o.group;
  }
};

struct IndexEntry {
  ResourceKey key;
  uint32_t unknown = 0;     // third index key field; constant 0 in shipped packages
  uint32_t offset = 0;      // absolute file offset of the stored bytes
  uint32_t diskSize = 0;    // stored size (high bit stripped)
  uint32_t memSize = 0;     // size after decompression
  bool compressed = false;  // 0xFFFF in the index means RefPack-compressed
  uint16_t committed = 0;
};

// Read-only DBPF 2.x / 3.x container ("DBPF" magic, 32-bit offsets).
class DatabasePackedFile {
 public:
  bool Open(const std::string& path);
  const std::string& Error() const { return error_; }
  uint32_t MajorVersion() const { return major_; }
  uint32_t MinorVersion() const { return minor_; }
  const std::vector<IndexEntry>& Entries() const { return entries_; }

  const IndexEntry* Find(const ResourceKey& key) const;
  // Raw stored bytes (still compressed if entry.compressed).
  std::optional<std::vector<uint8_t>> ReadRaw(const IndexEntry& e);
  // Decompressed contents; size always equals e.memSize on success.
  std::optional<std::vector<uint8_t>> Read(const IndexEntry& e);

 private:
  bool Fail(std::string msg) { error_ = std::move(msg); return false; }

  std::ifstream file_;
  uint64_t fileSize_ = 0;
  uint32_t major_ = 0, minor_ = 0;
  std::vector<IndexEntry> entries_;
  std::string error_;
};

}  // namespace Spore::Resource
