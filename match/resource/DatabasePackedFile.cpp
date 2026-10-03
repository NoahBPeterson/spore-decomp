#include "Resource/DatabasePackedFile.h"

namespace Resource {

// @ 0x008D8D90  (vtable slot 74h)
bool DatabasePackedFile::VerifyHeaderRecordIntegrity(const DBPFHeader* h) {
  bool valid = false;
  uint32_t fileSize = mpMemory ? mnMemorySize : mpStream->GetSize();
  if (h->magic == 0x46504244 && h->majorVersion <= 3 && h->indexCount < 0x7FFFFFF &&
      (uint32_t)h->indexOffset < fileSize &&
      h->indexSize + (uint32_t)h->indexOffset <= fileSize && h->indexMinor != 0)
    valid = true;
  if (h->indexOffset && h->indexOffsetV1) {
    if (h->indexOffset == h->indexOffsetV1)
      return true;
    return false;
  }
  return valid;
}

}  // namespace Resource
