// Type ID getter (0x010528c0): when both arguments are set, write the type ID 0xb0da49d9 to *out; always succeeds.
#include "game/types.h"

struct Object_10528c0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x010528c0
int Object_10528c0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xb0da49d9;
    return 1;
}
