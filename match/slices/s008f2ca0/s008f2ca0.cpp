// Setter (0x008f2ca0): store the dword argument in the member at +0x3ac.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2ca0 {
    char mPad[0x3ac];
    uint32_t mValue;                             // +0x3ac
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2ca0
void Owner_8f2ca0::SetValue(uint32_t value)
{
    mValue = value;
}
