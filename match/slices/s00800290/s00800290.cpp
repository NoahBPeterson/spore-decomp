// Type ID getter (0x00800290): when both arguments are set, write the type ID 0x02bcfc0e to *out; always succeeds.
#include "game/types.h"

struct Object_800290 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800290
int Object_800290::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x02bcfc0e;
    return 1;
}
