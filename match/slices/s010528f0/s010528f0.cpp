// Type ID getter (0x010528f0): when both arguments are set, write the type ID 0xf58c1654 to *out; always succeeds.
#include "game/types.h"

struct Object_10528f0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x010528f0
int Object_10528f0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xf58c1654;
    return 1;
}
