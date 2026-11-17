// Setter (0x00fccdd0): store the dword argument in the member at +0x4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_fccdd0 {
    char mPad[0x4];
    uint32_t mValue;                             // +0x4
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00fccdd0
void Owner_fccdd0::SetValue(uint32_t value)
{
    mValue = value;
}
