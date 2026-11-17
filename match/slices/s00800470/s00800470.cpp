// Type ID getter (0x00800470): when both arguments are set, write the type ID 0x033c9c5b to *out; always succeeds.
#include "game/types.h"

struct Object_800470 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800470
int Object_800470::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x033c9c5b;
    return 1;
}
