// Setter (0x00b2fba0): store the dword argument in the member at +0x154.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2fba0 {
    char mPad[0x154];
    uint32_t mValue;                             // +0x154
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00b2fba0
void Owner_b2fba0::SetValue(uint32_t value)
{
    mValue = value;
}
