// Type ID getter (0x01052ed0): when both arguments are set, write the type ID 0xa5d0d08f to *out; always succeeds.
#include "game/types.h"

struct Object_1052ed0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052ed0
int Object_1052ed0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xa5d0d08f;
    return 1;
}
