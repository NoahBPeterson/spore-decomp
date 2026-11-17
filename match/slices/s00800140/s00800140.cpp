// Type ID getter (0x00800140): when both arguments are set, write the type ID 0x015cbbd6 to *out; always succeeds.
#include "game/types.h"

struct Object_800140 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800140
int Object_800140::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x015cbbd6;
    return 1;
}
