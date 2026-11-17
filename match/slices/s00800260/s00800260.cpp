// Type ID getter (0x00800260): when both arguments are set, write the type ID 0x02bcfc18 to *out; always succeeds.
#include "game/types.h"

struct Object_800260 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800260
int Object_800260::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02bcfc18;
    return 1;
}
