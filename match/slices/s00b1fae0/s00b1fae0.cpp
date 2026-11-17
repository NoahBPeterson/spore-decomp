// Type ID getter (0x00b1fae0): when both arguments are set, write the type ID 0x0447341a to *out; always succeeds.
#include "game/types.h"

struct Object_b1fae0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b1fae0
int Object_b1fae0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0447341a;
    return 1;
}
