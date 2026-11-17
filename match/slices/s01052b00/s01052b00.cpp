// Type ID getter (0x01052b00): when both arguments are set, write the type ID 0x68eccb0a to *out; always succeeds.
#include "game/types.h"

struct Object_1052b00 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052b00
int Object_1052b00::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x68eccb0a;
    return 1;
}
