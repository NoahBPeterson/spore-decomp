// Setter (0x008f2cb0): store the dword argument in the member at +0x3b0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2cb0 {
    char mPad[0x3b0];
    uint32_t mValue;                             // +0x3b0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2cb0
void Owner_8f2cb0::SetValue(uint32_t value)
{
    mValue = value;
}
