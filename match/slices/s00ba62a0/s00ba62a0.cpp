// Type ID getter (0x00ba62a0): when both arguments are set, write the type ID 0x03e4353c to *out; always succeeds.
#include "game/types.h"

struct Object_ba62a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00ba62a0
int Object_ba62a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x03e4353c;
    return 1;
}
