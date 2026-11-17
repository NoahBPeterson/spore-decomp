// Type ID getter (0x00800170): when both arguments are set, write the type ID 0x04c04b4e to *out; always succeeds.
#include "game/types.h"

struct Object_800170 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800170
int Object_800170::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x04c04b4e;
    return 1;
}
