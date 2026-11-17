// Type ID getter (0x00ba6240): when both arguments are set, write the type ID 0x03e434e2 to *out; always succeeds.
#include "game/types.h"

struct Object_ba6240 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00ba6240
int Object_ba6240::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x03e434e2;
    return 1;
}
