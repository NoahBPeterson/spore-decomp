// Type ID getter (0x00b5c8a0): when both arguments are set, write the type ID 0x04238ecc to *out; always succeeds.
#include "game/types.h"

struct Object_b5c8a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c8a0
int Object_b5c8a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x04238ecc;
    return 1;
}
