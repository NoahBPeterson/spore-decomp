// Type ID getter (0x00b5c150): when both arguments are set, write the type ID 0x021f1187 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c150 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c150
int Object_b5c150::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x021f1187;
    return 1;
}
