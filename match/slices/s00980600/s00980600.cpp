// Type ID getter (0x00980600): when both arguments are set, write the type ID 0xcf2b2ad6 to *out; always succeeds.
#include "game/types.h"

struct Object_980600 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00980600
int Object_980600::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xcf2b2ad6;
    return 1;
}
