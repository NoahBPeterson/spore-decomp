// Type ID getter (0x008002f0): when both arguments are set, write the type ID 0x039a721c to *out; always succeeds.
#include "game/types.h"

struct Object_8002f0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008002f0
int Object_8002f0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x039a721c;
    return 1;
}
