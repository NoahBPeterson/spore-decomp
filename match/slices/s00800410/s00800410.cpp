// Type ID getter (0x00800410): when both arguments are set, write the type ID 0x0255e38e to *out; always succeeds.
#include "game/types.h"

struct Object_800410 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800410
int Object_800410::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0255e38e;
    return 1;
}
