// Type ID getter (0x00b5c000): when both arguments are set, write the type ID 0x021f10b2 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c000 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c000
int Object_b5c000::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x021f10b2;
    return 1;
}
