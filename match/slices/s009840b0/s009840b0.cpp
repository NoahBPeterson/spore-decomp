// Type ID getter (0x009840b0): when both arguments are set, write the type ID 0x2f00bdb3 to *out; always succeeds.
#include "game/types.h"

struct Object_9840b0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009840b0
int Object_9840b0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x2f00bdb3;
    return 1;
}
