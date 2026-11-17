// Type ID getter (0x00800230): when both arguments are set, write the type ID 0x02c200ce to *out; always succeeds.
#include "game/types.h"

struct Object_800230 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800230
int Object_800230::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02c200ce;
    return 1;
}
