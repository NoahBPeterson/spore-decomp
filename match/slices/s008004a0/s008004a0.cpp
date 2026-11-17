// Type ID getter (0x008004a0): when both arguments are set, write the type ID 0x0254cb67 to *out; always succeeds.
#include "game/types.h"

struct Object_8004a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008004a0
int Object_8004a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0254cb67;
    return 1;
}
