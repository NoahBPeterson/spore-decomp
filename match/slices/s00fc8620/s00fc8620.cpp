// Slice s00fc8620: IsMChunk, true for a chunk tag that starts with 'M' followed by 'V' or 'P'.
#include "types.h"

bool IsMChunk(const char* tag);

// @ 0x00fc8620
bool IsMChunk(const char* tag)
{
  if (tag[0] == 'M' && (tag[1] == 'V' || tag[1] == 'P'))
    return true;
  return false;
}
