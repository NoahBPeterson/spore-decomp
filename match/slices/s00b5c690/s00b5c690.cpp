// Type ID getter (0x00b5c690): when both arguments are set, write the type ID 0x02f011ed to *out; always succeeds.
#include "game/types.h"

struct Object_b5c690 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c690
int Object_b5c690::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02f011ed;
    return 1;
}
