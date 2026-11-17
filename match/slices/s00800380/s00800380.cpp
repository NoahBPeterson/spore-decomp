// Type ID getter (0x00800380): when both arguments are set, write the type ID 0x0109c69d to *out; always succeeds.
#include "game/types.h"

struct Object_800380 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800380
int Object_800380::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0109c69d;
    return 1;
}
