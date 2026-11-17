// Type ID getter (0x01052ad0): when both arguments are set, write the type ID 0x0eb54070 to *out; always succeeds.
#include "game/types.h"

struct Object_1052ad0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052ad0
int Object_1052ad0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0eb54070;
    return 1;
}
