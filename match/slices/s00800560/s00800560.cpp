// Type ID getter (0x00800560): when both arguments are set, write the type ID 0x0269a661 to *out; always succeeds.
#include "game/types.h"

struct Object_800560 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800560
int Object_800560::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0269a661;
    return 1;
}
