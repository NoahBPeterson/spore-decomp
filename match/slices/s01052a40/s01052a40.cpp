// Type ID getter (0x01052a40): when both arguments are set, write the type ID 0x2fd3eb55 to *out; always succeeds.
#include "game/types.h"

struct Object_1052a40 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052a40
int Object_1052a40::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x2fd3eb55;
    return 1;
}
