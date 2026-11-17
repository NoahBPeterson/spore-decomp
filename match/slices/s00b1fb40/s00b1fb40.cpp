// Type ID getter (0x00b1fb40): when both arguments are set, write the type ID 0x038cf94c to *out; always succeeds.
#include "game/types.h"

struct Object_b1fb40 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b1fb40
int Object_b1fb40::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x038cf94c;
    return 1;
}
