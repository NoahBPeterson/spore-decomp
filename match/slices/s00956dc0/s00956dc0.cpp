// Type ID getter (0x00956dc0): when both arguments are set, write the type ID 0x4ec1b8d8 to *out; always succeeds.
#include "game/types.h"

struct Object_956dc0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00956dc0
int Object_956dc0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x4ec1b8d8;
    return 1;
}
