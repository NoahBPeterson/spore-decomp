// Setter (0x00847b30): store the dword argument in the member at +0x78.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_847b30 {
    char mPad[0x78];
    uint32_t mValue;                             // +0x78
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00847b30
void Owner_847b30::SetValue(uint32_t value)
{
    mValue = value;
}
