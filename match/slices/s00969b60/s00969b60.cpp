// Type ID getter (0x00969b60): when both arguments are set, write the type ID 0xefbc56d8 to *out; always succeeds.
#include "game/types.h"

struct Object_969b60 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00969b60
int Object_969b60::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0xefbc56d8;
    return 1;
}
