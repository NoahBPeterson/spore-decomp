// Type ID getter (0x01052b90): when both arguments are set, write the type ID 0x63e333cb to *out; always succeeds.
#include "game/types.h"

struct Object_1052b90 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052b90
int Object_1052b90::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x63e333cb;
    return 1;
}
