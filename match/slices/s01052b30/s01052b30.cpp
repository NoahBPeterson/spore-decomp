// Type ID getter (0x01052b30): when both arguments are set, write the type ID 0xfc20c32d to *out; always succeeds.
#include "game/types.h"

struct Object_1052b30 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052b30
int Object_1052b30::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xfc20c32d;
    return 1;
}
