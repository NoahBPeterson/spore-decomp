// Type ID getter (0x00b5c0e0): when both arguments are set, write the type ID 0x3098af98 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c0e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c0e0
int Object_b5c0e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x3098af98;
    return 1;
}
