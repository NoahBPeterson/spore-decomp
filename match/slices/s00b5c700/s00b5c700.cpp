// Type ID getter (0x00b5c700): when both arguments are set, write the type ID 0x02f404ea to *out; always succeeds.
#include "game/types.h"

struct Object_b5c700 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c700
int Object_b5c700::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02f404ea;
    return 1;
}
