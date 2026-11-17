// Setter (0x007a4ab0): store the dword argument in the member at +0x18c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7a4ab0 {
    char mPad[0x18c];
    uint32_t mValue;                             // +0x18c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x007a4ab0
void Owner_7a4ab0::SetValue(uint32_t value)
{
    mValue = value;
}
