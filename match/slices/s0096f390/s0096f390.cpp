// Type ID getter (0x0096f390): when both arguments are set, write the type ID 0x030d54b9 to *out; always succeeds.
#include "game/types.h"

struct Object_96f390 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0096f390
int Object_96f390::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x030d54b9;
    return 1;
}
