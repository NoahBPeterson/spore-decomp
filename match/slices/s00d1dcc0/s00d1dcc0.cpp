// Setter (0x00d1dcc0): store the dword argument in the member at +0x130.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_d1dcc0 {
    char mPad[0x130];
    uint32_t mValue;                             // +0x130
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00d1dcc0
void Owner_d1dcc0::SetValue(uint32_t value)
{
    mValue = value;
}
