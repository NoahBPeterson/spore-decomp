// Setter (0x007cd950): store the dword argument in the member at +0x1c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7cd950 {
    char mPad[0x1c];
    uint32_t mValue;                             // +0x1c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x007cd950
void Owner_7cd950::SetValue(uint32_t value)
{
    mValue = value;
}
