// Type ID getter (0x009680c0): when both arguments are set, write the type ID 0xaf552c4b to *out; always succeeds.
#include "game/types.h"

struct Object_9680c0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009680c0
int Object_9680c0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xaf552c4b;
    return 1;
}
