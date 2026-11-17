// Type ID getter (0x00b5c5b0): when both arguments are set, write the type ID 0x058b3257 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c5b0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c5b0
int Object_b5c5b0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x058b3257;
    return 1;
}
