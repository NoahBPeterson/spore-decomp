// Type ID getter (0x008002c0): when both arguments are set, write the type ID 0x0372e920 to *out; always succeeds.
#include "game/types.h"

struct Object_8002c0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008002c0
int Object_8002c0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0372e920;
    return 1;
}
