// Type ID getter (0x0097e7a0): when both arguments are set, write the type ID 0xaf3df411 to *out; always succeeds.
#include "game/types.h"

struct Object_97e7a0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0097e7a0
int Object_97e7a0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xaf3df411;
    return 1;
}
