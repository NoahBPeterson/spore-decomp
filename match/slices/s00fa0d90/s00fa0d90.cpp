// Setter (0x00fa0d90): store the dword argument in the member at +0x1d0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_fa0d90 {
    char mPad[0x1d0];
    uint32_t mValue;                             // +0x1d0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00fa0d90
void Owner_fa0d90::SetValue(uint32_t value)
{
    mValue = value;
}
