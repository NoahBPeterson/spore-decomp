// Type ID getter (0x0096f0f0): when both arguments are set, write the type ID 0x6f2b6d2c to *out; always succeeds.
#include "game/types.h"

struct Object_96f0f0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0096f0f0
int Object_96f0f0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6f2b6d2c;
    return 1;
}
