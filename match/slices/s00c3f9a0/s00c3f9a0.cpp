// Setter (0x00c3f9a0): store the dword argument in the member at +0x110.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c3f9a0 {
    char mPad[0x110];
    uint32_t mValue;                             // +0x110
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c3f9a0
void Owner_c3f9a0::SetValue(uint32_t value)
{
    mValue = value;
}
