// Type ID getter (0x00800500): when both arguments are set, write the type ID 0x0253acd2 to *out; always succeeds.
#include "game/types.h"

struct Object_800500 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800500
int Object_800500::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0253acd2;
    return 1;
}
