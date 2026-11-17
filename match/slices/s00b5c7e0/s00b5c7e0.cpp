// Type ID getter (0x00b5c7e0): when both arguments are set, write the type ID 0x042232a1 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c7e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c7e0
int Object_b5c7e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x042232a1;
    return 1;
}
