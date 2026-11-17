// Setter (0x008f2820): store the dword argument in the member at +0x2a4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2820 {
    char mPad[0x2a4];
    uint32_t mValue;                             // +0x2a4
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2820
void Owner_8f2820::SetValue(uint32_t value)
{
    mValue = value;
}
