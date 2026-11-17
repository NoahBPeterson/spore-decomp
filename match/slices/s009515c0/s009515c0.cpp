// Type ID getter (0x009515c0): when both arguments are set, write the type ID 0x03852d17 to *out; always succeeds.
#include "game/types.h"

struct Object_9515c0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009515c0
int Object_9515c0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x03852d17;
    return 1;
}
