// Type ID getter (0x01052aa0): when both arguments are set, write the type ID 0x47531acd to *out; always succeeds.
#include "game/types.h"

struct Object_1052aa0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052aa0
int Object_1052aa0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x47531acd;
    return 1;
}
