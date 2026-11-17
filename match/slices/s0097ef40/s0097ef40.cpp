// Type ID getter (0x0097ef40): when both arguments are set, write the type ID 0x6f38282b to *out; always succeeds.
#include "game/types.h"

struct Object_97ef40 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0097ef40
int Object_97ef40::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x6f38282b;
    return 1;
}
