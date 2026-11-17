// Type ID getter (0x009818e0): when both arguments are set, write the type ID 0x8ef37d6d to *out; always succeeds.
#include "game/types.h"

struct Object_9818e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009818e0
int Object_9818e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x8ef37d6d;
    return 1;
}
