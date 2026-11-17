// Type ID getter (0x00b26760): when both arguments are set, write the type ID 0x12326f68 to *out; always succeeds.
#include "game/types.h"

struct Object_b26760 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b26760
int Object_b26760::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x12326f68;
    return 1;
}
