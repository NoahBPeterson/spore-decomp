// Type ID getter (0x00983ae0): when both arguments are set, write the type ID 0xef034604 to *out; always succeeds.
#include "game/types.h"

struct Object_983ae0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00983ae0
int Object_983ae0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xef034604;
    return 1;
}
