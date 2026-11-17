// Type ID getter (0x00b5c1c0): when both arguments are set, write the type ID 0x023ba44d to *out; always succeeds.
#include "game/types.h"

struct Object_b5c1c0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c1c0
int Object_b5c1c0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x023ba44d;
    return 1;
}
