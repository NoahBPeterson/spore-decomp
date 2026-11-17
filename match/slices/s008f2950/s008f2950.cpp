// Setter (0x008f2950): store the dword argument in the member at +0x2e0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2950 {
    char mPad[0x2e0];
    uint32_t mValue;                             // +0x2e0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2950
void Owner_8f2950::SetValue(uint32_t value)
{
    mValue = value;
}
