// Setter (0x007a4bd0): store the dword argument in the member at +0x88.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7a4bd0 {
    char mPad[0x88];
    uint32_t mValue;                             // +0x88
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x007a4bd0
void Owner_7a4bd0::SetValue(uint32_t value)
{
    mValue = value;
}
