// Type ID getter (0x00800590): when both arguments are set, write the type ID 0x0254aa82 to *out; always succeeds.
#include "game/types.h"

struct Object_800590 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800590
int Object_800590::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0254aa82;
    return 1;
}
