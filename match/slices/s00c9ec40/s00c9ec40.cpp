// Setter (0x00c9ec40): store the dword argument in the member at +0xbc4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c9ec40 {
    char mPad[0xbc4];
    uint32_t mValue;                             // +0xbc4
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c9ec40
void Owner_c9ec40::SetValue(uint32_t value)
{
    mValue = value;
}
