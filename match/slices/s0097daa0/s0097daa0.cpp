// Type ID getter (0x0097daa0): when both arguments are set, write the type ID 0x02cde37e to *out; always succeeds.
#include "game/types.h"

struct Object_97daa0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0097daa0
int Object_97daa0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02cde37e;
    return 1;
}
