// Type ID getter (0x01052a10): when both arguments are set, write the type ID 0x21d49382 to *out; always succeeds.
#include "game/types.h"

struct Object_1052a10 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052a10
int Object_1052a10::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x21d49382;
    return 1;
}
