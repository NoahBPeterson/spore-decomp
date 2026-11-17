// Type ID getter (0x01052980): when both arguments are set, write the type ID 0x733b280c to *out; always succeeds.
#include "game/types.h"

struct Object_1052980 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052980
int Object_1052980::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x733b280c;
    return 1;
}
