// Type ID getter (0x01052ce0): when both arguments are set, write the type ID 0x0223be7b to *out; always succeeds.
#include "game/types.h"

struct Object_1052ce0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052ce0
int Object_1052ce0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0223be7b;
    return 1;
}
