// Type ID getter (0x008003b0): when both arguments are set, write the type ID 0x04ea92a3 to *out; always succeeds.
#include "game/types.h"

struct Object_8003b0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008003b0
int Object_8003b0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x04ea92a3;
    return 1;
}
