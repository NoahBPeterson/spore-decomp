// Type ID getter (0x008000b0): when both arguments are set, write the type ID 0x0279bf9e to *out; always succeeds.
#include "game/types.h"

struct Object_8000b0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008000b0
int Object_8000b0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0279bf9e;
    return 1;
}
