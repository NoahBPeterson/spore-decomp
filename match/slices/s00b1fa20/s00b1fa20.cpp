// Type ID getter (0x00b1fa20): when both arguments are set, write the type ID 0x03a3ac9f to *out; always succeeds.
#include "game/types.h"

struct Object_b1fa20 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b1fa20
int Object_b1fa20::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x03a3ac9f;
    return 1;
}
