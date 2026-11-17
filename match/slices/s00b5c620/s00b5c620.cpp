// Type ID getter (0x00b5c620): when both arguments are set, write the type ID 0x02a8bfbe to *out; always succeeds.
#include "game/types.h"

struct Object_b5c620 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c620
int Object_b5c620::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02a8bfbe;
    return 1;
}
