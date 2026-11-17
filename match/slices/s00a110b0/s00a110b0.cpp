// Setter (0x00a110b0): store the dword argument in the member at +0xd0c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a110b0 {
    char mPad[0xd0c];
    uint32_t mValue;                             // +0xd0c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00a110b0
void Owner_a110b0::SetValue(uint32_t value)
{
    mValue = value;
}
