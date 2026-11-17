// Type ID getter (0x00992f80): when both arguments are set, write the type ID 0x04d04553 to *out; always succeeds.
#include "game/types.h"

struct Object_992f80 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00992f80
int Object_992f80::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x04d04553;
    return 1;
}
