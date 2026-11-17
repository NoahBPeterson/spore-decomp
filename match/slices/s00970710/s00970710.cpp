// Setter (0x00970710): store the dword argument in the member at +0x68.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_970710 {
    char mPad[0x68];
    uint32_t mValue;                             // +0x68
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00970710
void Owner_970710::SetValue(uint32_t value)
{
    mValue = value;
}
