// Type ID getter (0x01052c80): when both arguments are set, write the type ID 0xc0b1ae6a to *out; always succeeds.
#include "game/types.h"

struct Object_1052c80 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052c80
int Object_1052c80::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xc0b1ae6a;
    return 1;
}
