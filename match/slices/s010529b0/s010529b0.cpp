// Type ID getter (0x010529b0): when both arguments are set, write the type ID 0x7d4f4d72 to *out; always succeeds.
#include "game/types.h"

struct Object_10529b0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x010529b0
int Object_10529b0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x7d4f4d72;
    return 1;
}
