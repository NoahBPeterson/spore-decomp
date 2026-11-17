// Type ID getter (0x00800200): when both arguments are set, write the type ID 0x0238ea36 to *out; always succeeds.
#include "game/types.h"

struct Object_800200 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00800200
int Object_800200::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0238ea36;
    return 1;
}
