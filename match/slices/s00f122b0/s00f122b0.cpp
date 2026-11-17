// Type ID getter (0x00f122b0): when both arguments are set, write the type ID 0x07c3bd3e to *out; always succeeds.
#include "game/types.h"

struct Object_f122b0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00f122b0
int Object_f122b0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x07c3bd3e;
    return 1;
}
