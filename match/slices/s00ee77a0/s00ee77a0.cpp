// Type ID getter (0x00ee77a0): when both arguments are set, write the type ID 0xd1c304c2 to *out; always succeeds.
#include "game/types.h"

struct Object_ee77a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00ee77a0
int Object_ee77a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xd1c304c2;
    return 1;
}
