// Type ID getter (0x01052c20): when both arguments are set, write the type ID 0x3e5e4a39 to *out; always succeeds.
#include "game/types.h"

struct Object_1052c20 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052c20
int Object_1052c20::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x3e5e4a39;
    return 1;
}
