// Type ID getter (0x00b5c3f0): when both arguments are set, write the type ID 0x02cb0ee3 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c3f0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c3f0
int Object_b5c3f0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02cb0ee3;
    return 1;
}
