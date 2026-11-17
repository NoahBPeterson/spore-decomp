// Type ID getter (0x00e4f630): when both arguments are set, write the type ID 0xabcdef00 to *out; always succeeds.
#include "game/types.h"

struct Object_e4f630 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00e4f630
int Object_e4f630::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xabcdef00;
    return 1;
}
