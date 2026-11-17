// Type ID getter (0x00ed1d40): when both arguments are set, write the type ID 0x8057a1e0 to *out; always succeeds.
#include "game/types.h"

struct Object_ed1d40 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00ed1d40
int Object_ed1d40::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x8057a1e0;
    return 1;
}
