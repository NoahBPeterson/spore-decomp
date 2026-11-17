// Type ID getter (0x00b5c460): when both arguments are set, write the type ID 0x02aa56d0 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c460 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c460
int Object_b5c460::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02aa56d0;
    return 1;
}
