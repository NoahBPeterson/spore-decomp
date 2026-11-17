// Type ID getter (0x01052bc0): when both arguments are set, write the type ID 0x8a8b6f35 to *out; always succeeds.
#include "game/types.h"

struct Object_1052bc0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052bc0
int Object_1052bc0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x8a8b6f35;
    return 1;
}
