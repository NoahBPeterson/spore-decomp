// Type ID getter (0x009888f0): when both arguments are set, write the type ID 0x6f15f51b to *out; always succeeds.
#include "game/types.h"

struct Object_9888f0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009888f0
int Object_9888f0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6f15f51b;
    return 1;
}
