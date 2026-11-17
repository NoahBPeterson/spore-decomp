// Type ID getter (0x00800320): when both arguments are set, write the type ID 0x0540037e to *out; always succeeds.
#include "game/types.h"

struct Object_800320 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800320
int Object_800320::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0540037e;
    return 1;
}
