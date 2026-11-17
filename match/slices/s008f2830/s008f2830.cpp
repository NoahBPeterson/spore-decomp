// Setter (0x008f2830): store the dword argument in the member at +0x2a8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2830 {
    char mPad[0x2a8];
    uint32_t mValue;                             // +0x2a8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2830
void Owner_8f2830::SetValue(uint32_t value)
{
    mValue = value;
}
