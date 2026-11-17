// Setter (0x007763e0): store the dword argument in the member at +0x1bc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7763e0 {
    char mPad[0x1bc];
    uint32_t mValue;                             // +0x1bc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x007763e0
void Owner_7763e0::SetValue(uint32_t value)
{
    mValue = value;
}
