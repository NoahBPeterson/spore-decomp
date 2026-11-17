// Type ID getter (0x008003e0): when both arguments are set, write the type ID 0x024ba741 to *out; always succeeds.
#include "game/types.h"

struct Object_8003e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008003e0
int Object_8003e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x024ba741;
    return 1;
}
