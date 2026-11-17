// Type ID getter (0x0098f300): when both arguments are set, write the type ID 0xf02c7c44 to *out; always succeeds.
#include "game/types.h"

struct Object_98f300 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0098f300
int Object_98f300::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xf02c7c44;
    return 1;
}
