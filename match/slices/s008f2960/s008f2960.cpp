// Setter (0x008f2960): store the dword argument in the member at +0x250.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2960 {
    char mPad[0x250];
    uint32_t mValue;                             // +0x250
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2960
void Owner_8f2960::SetValue(uint32_t value)
{
    mValue = value;
}
