// Type ID getter (0x00b5c910): when both arguments are set, write the type ID 0x018eb5c7 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c910 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c910
int Object_b5c910::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x018eb5c7;
    return 1;
}
