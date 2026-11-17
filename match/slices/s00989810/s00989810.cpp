// Type ID getter (0x00989810): when both arguments are set, write the type ID 0x6f42b4f0 to *out; always succeeds.
#include "game/types.h"

struct Object_989810 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00989810
int Object_989810::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6f42b4f0;
    return 1;
}
