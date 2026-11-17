// Type ID getter (0x01039700): when both arguments are set, write the type ID 0x05b82efa to *out; always succeeds.
#include "game/types.h"

struct Object_1039700 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01039700
int Object_1039700::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x05b82efa;
    return 1;
}
