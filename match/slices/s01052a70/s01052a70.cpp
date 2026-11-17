// Type ID getter (0x01052a70): when both arguments are set, write the type ID 0x00be727b to *out; always succeeds.
#include "game/types.h"

struct Object_1052a70 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052a70
int Object_1052a70::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x00be727b;
    return 1;
}
