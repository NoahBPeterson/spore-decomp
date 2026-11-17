// Type ID getter (0x00b5c840): when both arguments are set, write the type ID 0x0424ea07 to *out; always succeeds.
#include "game/types.h"

struct Object_b5c840 {
    int GetTypeID(uint32_t* out, int want);
};

// @ 0x00b5c840
int Object_b5c840::GetTypeID(uint32_t* out, int want)
{
    if (out && want)
        *out = 0x0424ea07;
    return 1;
}
