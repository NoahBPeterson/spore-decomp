// Type ID getter (0x01052cb0): when both arguments are set, write the type ID 0x72e076a7 to *out; always succeeds.
#include "game/types.h"

struct Object_1052cb0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052cb0
int Object_1052cb0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x72e076a7;
    return 1;
}
