// Type ID getter (0x00986170): when both arguments are set, write the type ID 0x4f063bb3 to *out; always succeeds.
#include "game/types.h"

struct Object_986170 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00986170
int Object_986170::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x4f063bb3;
    return 1;
}
