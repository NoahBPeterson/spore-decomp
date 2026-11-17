// Type ID getter (0x00800530): when both arguments are set, write the type ID 0x0253add9 to *out; always succeeds.
#include "game/types.h"

struct Object_800530 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800530
int Object_800530::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0253add9;
    return 1;
}
