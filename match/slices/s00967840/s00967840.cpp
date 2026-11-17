// Type ID getter (0x00967840): when both arguments are set, write the type ID 0x2f552cce to *out; always succeeds.
#include "game/types.h"

struct Object_967840 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00967840
int Object_967840::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x2f552cce;
    return 1;
}
