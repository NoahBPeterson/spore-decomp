// Setter (0x00b18d70): store the dword argument in the member at +0x60.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b18d70 {
    char mPad[0x60];
    uint32_t mValue;                             // +0x60
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00b18d70
void Owner_b18d70::SetValue(uint32_t value)
{
    mValue = value;
}
