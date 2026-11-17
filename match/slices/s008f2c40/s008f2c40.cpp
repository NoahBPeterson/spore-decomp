// Setter (0x008f2c40): store the dword argument in the member at +0x380.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2c40 {
    char mPad[0x380];
    uint32_t mValue;                             // +0x380
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2c40
void Owner_8f2c40::SetValue(uint32_t value)
{
    mValue = value;
}
