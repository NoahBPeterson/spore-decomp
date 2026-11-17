// Setter (0x00b33cf0): store the dword argument in the member at +0x100.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b33cf0 {
    char mPad[0x100];
    uint32_t mValue;                             // +0x100
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00b33cf0
void Owner_b33cf0::SetValue(uint32_t value)
{
    mValue = value;
}
