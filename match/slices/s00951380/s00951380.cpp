// Type ID getter (0x00951380): when both arguments are set, write the type ID 0x03852d14 to *out; always succeeds.
#include "game/types.h"

struct Object_951380 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00951380
int Object_951380::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x03852d14;
    return 1;
}
