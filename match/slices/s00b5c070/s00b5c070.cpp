// Type ID getter (0x00b5c070): when both arguments are set, write the type ID 0x021f1105 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c070 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c070
int Object_b5c070::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x021f1105;
    return 1;
}
