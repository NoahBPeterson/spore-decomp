// Type ID getter (0x00800880): when both arguments are set, write the type ID 0x0106f61e to *out; always succeeds.
#include "game/types.h"

struct Object_800880 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800880
int Object_800880::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0106f61e;
    return 1;
}
