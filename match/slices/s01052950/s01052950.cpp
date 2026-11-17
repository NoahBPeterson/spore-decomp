// Type ID getter (0x01052950): when both arguments are set, write the type ID 0xd001f5e2 to *out; always succeeds.
#include "game/types.h"

struct Object_1052950 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052950
int Object_1052950::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xd001f5e2;
    return 1;
}
