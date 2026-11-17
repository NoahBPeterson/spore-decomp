// Setter (0x00bd81e0): store the dword argument in the member at +0x2f0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bd81e0 {
    char mPad[0x2f0];
    uint32_t mValue;                             // +0x2f0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00bd81e0
void Owner_bd81e0::SetValue(uint32_t value)
{
    mValue = value;
}
