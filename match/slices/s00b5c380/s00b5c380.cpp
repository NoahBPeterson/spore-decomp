// Type ID getter (0x00b5c380): when both arguments are set, write the type ID 0x02e1923c to *out; always succeeds.
#include "game/types.h"

struct Object_b5c380 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c380
int Object_b5c380::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02e1923c;
    return 1;
}
