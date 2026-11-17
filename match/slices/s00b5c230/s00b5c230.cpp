// Type ID getter (0x00b5c230): when both arguments are set, write the type ID 0x021f11ae to *out; always succeeds.
#include "game/types.h"

struct Object_b5c230 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c230
int Object_b5c230::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x021f11ae;
    return 1;
}
