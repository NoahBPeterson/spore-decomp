// Type ID getter (0x00987ab0): when both arguments are set, write the type ID 0xb03c196f to *out; always succeeds.
#include "game/types.h"

struct Object_987ab0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00987ab0
int Object_987ab0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xb03c196f;
    return 1;
}
