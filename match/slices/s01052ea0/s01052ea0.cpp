// Type ID getter (0x01052ea0): when both arguments are set, write the type ID 0x02c2b837 to *out; always succeeds.
#include "game/types.h"

struct Object_1052ea0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052ea0
int Object_1052ea0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02c2b837;
    return 1;
}
