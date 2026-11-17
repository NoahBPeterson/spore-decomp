// Type ID getter (0x00800350): when both arguments are set, write the type ID 0x053eb32a to *out; always succeeds.
#include "game/types.h"

struct Object_800350 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800350
int Object_800350::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x053eb32a;
    return 1;
}
