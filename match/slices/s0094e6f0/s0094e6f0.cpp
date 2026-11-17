// Setter (0x0094e6f0): store the dword argument in the member at +0x70.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_94e6f0 {
    char mPad[0x70];
    uint32_t mValue;                             // +0x70
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0094e6f0
void Owner_94e6f0::SetValue(uint32_t value)
{
    mValue = value;
}
