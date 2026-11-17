// Type ID getter (0x00b1fa80): when both arguments are set, write the type ID 0x037abb4a to *out; always succeeds.
#include "game/types.h"

struct Object_b1fa80 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b1fa80
int Object_b1fa80::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x037abb4a;
    return 1;
}
