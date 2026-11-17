// Setter (0x00a16a30): store the dword argument in the member at +0x5c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a16a30 {
    char mPad[0x5c];
    uint32_t mValue;                             // +0x5c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00a16a30
void Owner_a16a30::SetValue(uint32_t value)
{
    mValue = value;
}
