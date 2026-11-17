// Type ID getter (0x00963e70): when both arguments are set, write the type ID 0xaf3a9e26 to *out; always succeeds.
#include "game/types.h"

struct Object_963e70 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00963e70
int Object_963e70::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xaf3a9e26;
    return 1;
}
