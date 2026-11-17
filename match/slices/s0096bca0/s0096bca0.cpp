// Type ID getter (0x0096bca0): when both arguments are set, write the type ID 0x0f0b8b73 to *out; always succeeds.
#include "game/types.h"

struct Object_96bca0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0096bca0
int Object_96bca0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0f0b8b73;
    return 1;
}
