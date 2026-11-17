// Type ID getter (0x008001a0): when both arguments are set, write the type ID 0x04c04b4d to *out; always succeeds.
#include "game/types.h"

struct Object_8001a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008001a0
int Object_8001a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x04c04b4d;
    return 1;
}
