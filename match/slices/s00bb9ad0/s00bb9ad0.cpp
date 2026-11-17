// Setter (0x00bb9ad0): store the dword argument in the member at +0x4c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bb9ad0 {
    char mPad[0x4c];
    uint32_t mValue;                             // +0x4c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00bb9ad0
void Owner_bb9ad0::SetValue(uint32_t value)
{
    mValue = value;
}
