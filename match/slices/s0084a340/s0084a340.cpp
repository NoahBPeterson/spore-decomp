// Setter (0x0084a340): store the dword argument in the member at +0xcc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_84a340 {
    char mPad[0xcc];
    uint32_t mValue;                             // +0xcc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0084a340
void Owner_84a340::SetValue(uint32_t value)
{
    mValue = value;
}
