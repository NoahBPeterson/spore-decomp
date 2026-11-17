// Type ID getter (0x00980730): when both arguments are set, write the type ID 0xaf8772af to *out; always succeeds.
#include "game/types.h"

struct Object_980730 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00980730
int Object_980730::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xaf8772af;
    return 1;
}
