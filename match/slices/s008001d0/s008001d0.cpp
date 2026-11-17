// Type ID getter (0x008001d0): when both arguments are set, write the type ID 0x02086743 to *out; always succeeds.
#include "game/types.h"

struct Object_8001d0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x008001d0
int Object_8001d0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02086743;
    return 1;
}
