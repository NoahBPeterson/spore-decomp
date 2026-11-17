// Type ID getter (0x008000e0): when both arguments are set, write the type ID 0x0106f14b to *out; always succeeds.
#include "game/types.h"

struct Object_8000e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008000e0
int Object_8000e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0106f14b;
    return 1;
}
