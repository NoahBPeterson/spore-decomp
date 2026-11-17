// Type ID getter (0x0096b330): when both arguments are set, write the type ID 0x6f0c7aea to *out; always succeeds.
#include "game/types.h"

struct Object_96b330 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0096b330
int Object_96b330::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6f0c7aea;
    return 1;
}
