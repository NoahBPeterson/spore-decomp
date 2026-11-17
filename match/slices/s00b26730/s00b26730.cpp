// Type ID getter (0x00b26730): when both arguments are set, write the type ID 0x04162ca7 to *out; always succeeds.
#include "game/types.h"

struct Object_b26730 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b26730
int Object_b26730::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x04162ca7;
    return 1;
}
