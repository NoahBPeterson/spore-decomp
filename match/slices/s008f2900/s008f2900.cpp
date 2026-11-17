// Setter (0x008f2900): store the dword argument in the member at +0x260.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2900 {
    char mPad[0x260];
    uint32_t mValue;                             // +0x260
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2900
void Owner_8f2900::SetValue(uint32_t value)
{
    mValue = value;
}
