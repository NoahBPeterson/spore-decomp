// Type ID getter (0x00800110): when both arguments are set, write the type ID 0x010ede03 to *out; always succeeds.
#include "game/types.h"

struct Object_800110 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800110
int Object_800110::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x010ede03;
    return 1;
}
