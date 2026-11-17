// Type ID getter (0x0098f2d0): when both arguments are set, write the type ID 0x702c5143 to *out; always succeeds.
#include "game/types.h"

struct Object_98f2d0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0098f2d0
int Object_98f2d0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x702c5143;
    return 1;
}
