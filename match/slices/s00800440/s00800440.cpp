// Type ID getter (0x00800440): when both arguments are set, write the type ID 0x025611ed to *out; always succeeds.
#include "game/types.h"

struct Object_800440 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800440
int Object_800440::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x025611ed;
    return 1;
}
