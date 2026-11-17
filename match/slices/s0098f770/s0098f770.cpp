// Type ID getter (0x0098f770): when both arguments are set, write the type ID 0xf02aff4b to *out; always succeeds.
#include "game/types.h"

struct Object_98f770 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0098f770
int Object_98f770::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xf02aff4b;
    return 1;
}
