// Type ID getter (0x00ee7730): when both arguments are set, write the type ID 0x3ca760f2 to *out; always succeeds.
#include "game/types.h"

struct Object_ee7730 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00ee7730
int Object_ee7730::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x3ca760f2;
    return 1;
}
