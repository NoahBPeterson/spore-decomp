#pragma once
#include "types.h"
#include "IO/IStream.h"

namespace Resource {

// On-disk DBPF header (0x60 bytes) as read by ReadHeaderRecord @ 0x008D8C50.
struct DBPFHeader {
  uint32_t magic;          // 0x00 'DBPF'
  uint32_t majorVersion;   // 0x04
  uint32_t minorVersion;   // 0x08
  uint32_t userMajor;      // 0x0C
  uint32_t userMinor;      // 0x10
  uint32_t flags;          // 0x14
  uint32_t createdDate;    // 0x18
  uint32_t modifiedDate;   // 0x1C
  uint32_t indexMajor;     // 0x20
  uint32_t indexCount;     // 0x24
  uint32_t indexOffsetV1;  // 0x28 legacy
  uint32_t indexSize;      // 0x2C
  uint32_t holeCount;      // 0x30
  uint32_t holeOffset;     // 0x34
  uint32_t holeSize;       // 0x38
  uint32_t indexMinor;     // 0x3C
  uint64_t indexOffset;    // 0x40
  uint8_t reserved[0x18];  // 0x48
};

// Partial layout of Resource::DatabasePackedFile (vtable 0x014367B0, size 0x388 per ModAPI).
// Only fields touched by matched functions are named; the rest is padding at exact offsets.
class DatabasePackedFile {
 public:
  bool VerifyHeaderRecordIntegrity(const DBPFHeader* header);  // vt 74h, @ 0x008D8D90

 private:
  uint8_t mPad000[0x260];
  IO::IStream* mpStream;    // 0x260
  const uint8_t* mpMemory;  // 0x264 non-null when the package is memory-backed
  uint32_t mnMemorySize;    // 0x268
};

}  // namespace Resource
