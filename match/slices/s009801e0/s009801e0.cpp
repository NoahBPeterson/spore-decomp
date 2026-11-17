// Type ID getter (0x009801e0): when both arguments are set, write the type ID 0x2f8bbb4d to *out; always succeeds.
#include "game/types.h"

struct Object_9801e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x009801e0
int Object_9801e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x2f8bbb4d;
    return 1;
}
