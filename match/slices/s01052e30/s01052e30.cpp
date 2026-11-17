// Type ID getter (0x01052e30): when both arguments are set, write the type ID 0x032229ff to *out; always succeeds.
#include "game/types.h"

struct Object_1052e30 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052e30
int Object_1052e30::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x032229ff;
    return 1;
}
