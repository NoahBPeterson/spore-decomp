// Type ID getter (0x009925d0): when both arguments are set, write the type ID 0x6fb339c9 to *out; always succeeds.
#include "game/types.h"

struct Object_9925d0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009925d0
int Object_9925d0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6fb339c9;
    return 1;
}
