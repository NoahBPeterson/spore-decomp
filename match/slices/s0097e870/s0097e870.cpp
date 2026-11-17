// Type ID getter (0x0097e870): when both arguments are set, write the type ID 0x2f418d72 to *out; always succeeds.
#include "game/types.h"

struct Object_97e870 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x0097e870
int Object_97e870::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x2f418d72;
    return 1;
}
