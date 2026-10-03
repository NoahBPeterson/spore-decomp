#pragma once
#include <cstdint>
#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>
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

// The original index hash (0x008DB450) is instance ^ group, modulo bucket count.
struct ResourceKeyHash {
  size_t operator()(const ResourceKey& k) const { return k.instance ^ k.group; }
};

// Mirrors the 0x20-byte index node built by PFIndexModifiable::Read (0x008DB9B0).
struct IndexEntry {
  ResourceKey key;
  uint32_t offset = 0;       // relative to the header position
  uint32_t diskSize = 0;     // stored size, high bit stripped
  uint32_t memSize = 0;      // size after decompression
  uint16_t compression = 0;  // 0 = stored; any other value = RefPack
  bool committed = false;
  bool IsCompressed() const { return compression != 0; }
};

// Header fields DatabasePackedFile::ReadHeaderRecord (0x008D8C50) keeps.
struct HeaderRecord {
  uint32_t userMajor = 0;     // +0x0C
  uint32_t userMinor = 0;     // +0x10
  uint32_t createdDate = 0;   // +0x18
  uint32_t modifiedDate = 0;  // +0x1C
  uint32_t indexMajor = 0;    // +0x20
  uint32_t indexOffset = 0;   // +0x40, or legacy +0x28 when +0x40 is zero
  uint32_t indexCount = 0;    // +0x24
  uint32_t indexSize = 0;     // +0x2C
};

// Read-only reimplementation of Resource::DatabasePackedFile (vtable 0x014367B0).
class DatabasePackedFile {
 public:
  bool Open(const std::string& path);
  const std::string& Error() const { return error_; }
  const HeaderRecord& Header() const { return header_; }
  uint32_t HeaderPosition() const { return headerPosition_; }
  // Entries in index order, including duplicates the lookup map ignores.
  const std::vector<IndexEntry>& Entries() const { return entries_; }

  // Lookup with the original's first-entry-wins semantics for duplicate keys.
  const IndexEntry* Find(const ResourceKey& key) const;
  // Raw stored bytes (still compressed if entry.IsCompressed()).
  std::optional<std::vector<uint8_t>> ReadRaw(const IndexEntry& e);
  // Decompressed contents (0x008D9320 / 0x008D8820 for compressed records).
  std::optional<std::vector<uint8_t>> Read(const IndexEntry& e);

  // Exposed for tests. Each mirrors the original function at the noted address.
  static bool VerifyHeaderRecordIntegrity(const uint8_t header[0x60], uint64_t fileSize);  // 0x008D8D90
  static bool ParseIndex(const uint8_t* data, size_t size, uint32_t count, bool committed,
                         std::vector<IndexEntry>& out);                                     // 0x008DB9B0
  static bool VerifyIndexRecordIntegrity(const std::vector<IndexEntry>& entries,
                                         uint64_t lo, uint64_t hi);                          // 0x008DB280
  static int64_t FindEmbeddedHeader(std::istream& in, uint64_t fileSize);                    // 0x008DD510

 private:
  bool ReadHeaderRecord(bool allowRetry);  // 0x008D8C50
  bool ReadIndexRecord();                  // 0x008DA750
  bool ReadAt(uint64_t pos, void* dst, size_t n, size_t* got);  // 0x008D9050 + 0x008D88D0
  bool Fail(std::string msg) { error_ = std::move(msg); return false; }

  std::ifstream file_;
  uint64_t fileSize_ = 0;
  uint32_t headerPosition_ = 0;
  HeaderRecord header_;
  std::vector<IndexEntry> entries_;
  std::unordered_map<ResourceKey, size_t, ResourceKeyHash> lookup_;
  std::string error_;
};

}  // namespace Spore::Resource
