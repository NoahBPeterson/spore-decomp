// Setter (0x00c9e870): store the dword argument in the member at +0xc38.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c9e870 {
    char mPad[0xc38];
    uint32_t mValue;                             // +0xc38
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c9e870
void Owner_c9e870::SetValue(uint32_t value)
{
    mValue = value;
}
