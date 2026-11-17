// Setter (0x00c03170): store the dword argument in the member at +0x1680.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c03170 {
    char mPad[0x1680];
    uint32_t mValue;                             // +0x1680
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c03170
void Owner_c03170::SetValue(uint32_t value)
{
    mValue = value;
}
