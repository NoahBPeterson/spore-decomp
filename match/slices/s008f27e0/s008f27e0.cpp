// Setter (0x008f27e0): store the dword argument in the member at +0x28c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f27e0 {
    char mPad[0x28c];
    uint32_t mValue;                             // +0x28c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f27e0
void Owner_8f27e0::SetValue(uint32_t value)
{
    mValue = value;
}
