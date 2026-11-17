// Type ID getter (0x01052b60): when both arguments are set, write the type ID 0x6cb0b689 to *out; always succeeds.
#include "game/types.h"

struct Object_1052b60 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x01052b60
int Object_1052b60::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6cb0b689;
    return 1;
}
