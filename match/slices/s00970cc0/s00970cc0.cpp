// Type ID getter (0x00970cc0): when both arguments are set, write the type ID 0x6f1f1aa6 to *out; always succeeds.
#include "game/types.h"

struct Object_970cc0 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00970cc0
int Object_970cc0::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6f1f1aa6;
    return 1;
}
