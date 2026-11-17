// Setter (0x00b33ce0): store the dword argument in the member at +0xfc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b33ce0 {
    char mPad[0xfc];
    uint32_t mValue;                             // +0xfc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00b33ce0
void Owner_b33ce0::SetValue(uint32_t value)
{
    mValue = value;
}
