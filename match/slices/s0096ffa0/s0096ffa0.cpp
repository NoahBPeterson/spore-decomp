// Type ID getter (0x0096ffa0): when both arguments are set, write the type ID 0xcf2b2ad4 to *out; always succeeds.
#include "game/types.h"

struct Object_96ffa0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0096ffa0
int Object_96ffa0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xcf2b2ad4;
    return 1;
}
