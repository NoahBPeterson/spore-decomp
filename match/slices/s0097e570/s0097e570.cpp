// Type ID getter (0x0097e570): when both arguments are set, write the type ID 0x4f3daf02 to *out; always succeeds.
#include "game/types.h"

struct Object_97e570 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0097e570
int Object_97e570::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x4f3daf02;
    return 1;
}
