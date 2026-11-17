// Type ID getter (0x00b5c4d0): when both arguments are set, write the type ID 0xd406729f to *out; always succeeds.
#include "game/types.h"

struct Object_b5c4d0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c4d0
int Object_b5c4d0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xd406729f;
    return 1;
}
