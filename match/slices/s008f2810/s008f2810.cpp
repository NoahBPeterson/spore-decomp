// Setter (0x008f2810): store the dword argument in the member at +0x2a0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2810 {
    char mPad[0x2a0];
    uint32_t mValue;                             // +0x2a0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2810
void Owner_8f2810::SetValue(uint32_t value)
{
    mValue = value;
}
