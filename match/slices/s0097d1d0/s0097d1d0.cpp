// Type ID getter (0x0097d1d0): when both arguments are set, write the type ID 0xcf3c4eae to *out; always succeeds.
#include "game/types.h"

struct Object_97d1d0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0097d1d0
int Object_97d1d0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xcf3c4eae;
    return 1;
}
