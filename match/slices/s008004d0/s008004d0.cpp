// Type ID getter (0x008004d0): when both arguments are set, write the type ID 0x033f7ad6 to *out; always succeeds.
#include "game/types.h"

struct Object_8004d0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008004d0
int Object_8004d0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x033f7ad6;
    return 1;
}
