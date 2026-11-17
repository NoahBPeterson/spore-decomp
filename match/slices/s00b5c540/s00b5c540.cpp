// Type ID getter (0x00b5c540): when both arguments are set, write the type ID 0x74336f3e to *out; always succeeds.
#include "game/types.h"

struct Object_b5c540 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c540
int Object_b5c540::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x74336f3e;
    return 1;
}
