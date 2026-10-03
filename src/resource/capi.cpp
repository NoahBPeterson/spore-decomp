// C ABI over the resource layer, used by the differential-test harness (ctypes).
#include <cstring>

#include "resource/DBPF.h"
#include "resource/Hash.h"
#include "resource/RefPack.h"

using namespace Spore::Resource;

extern "C" {

uint32_t spore_hash_name(const char* s, size_t n) { return HashName(std::string_view(s, n)); }

// Returns decompressed size, or -1 on failure. dst may be null to query the size.
int64_t spore_refpack_decompress(const uint8_t* src, size_t n, uint8_t* dst, size_t dstCap) {
  if (!dst) {
    auto size = RefPackDecompressedSize(src, n);
    return size ? int64_t(*size) : -1;
  }
  auto out = RefPackDecompress(src, n);
  if (!out || out->size() > dstCap) return -1;
  std::memcpy(dst, out->data(), out->size());
  return int64_t(out->size());
}

int spore_verify_header(const uint8_t* header, uint64_t fileSize) {
  return DatabasePackedFile::VerifyHeaderRecordIntegrity(header, fileSize) ? 1 : 0;
}

}  // extern "C"
