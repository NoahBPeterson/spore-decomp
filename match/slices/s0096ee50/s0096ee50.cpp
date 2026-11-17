// Type ID getter (0x0096ee50): when both arguments are set, write the type ID 0x4f8772aa to *out; always succeeds.
#include "game/types.h"

struct Object_96ee50 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0096ee50
int Object_96ee50::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x4f8772aa;
    return 1;
}
