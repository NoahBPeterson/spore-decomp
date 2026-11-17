// Type ID getter (0x010529e0): when both arguments are set, write the type ID 0x28ae31de to *out; always succeeds.
#include "game/types.h"

struct Object_10529e0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x010529e0
int Object_10529e0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x28ae31de;
    return 1;
}
