// Type ID getter (0x00b5c770): when both arguments are set, write the type ID 0x3226d7d4 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c770 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c770
int Object_b5c770::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x3226d7d4;
    return 1;
}
