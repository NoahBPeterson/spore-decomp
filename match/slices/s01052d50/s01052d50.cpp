// Type ID getter (0x01052d50): when both arguments are set, write the type ID 0x0384f82a to *out; always succeeds.
#include "game/types.h"

struct Object_1052d50 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052d50
int Object_1052d50::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0384f82a;
    return 1;
}
