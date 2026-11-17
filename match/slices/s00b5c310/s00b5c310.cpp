// Type ID getter (0x00b5c310): when both arguments are set, write the type ID 0x021f11c4 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c310 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c310
int Object_b5c310::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x021f11c4;
    return 1;
}
