// Setter (0x0095fa40): store the dword argument in the member at +0xbc.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_95fa40 {
    char mPad[0xbc];
    uint32_t mValue;                             // +0xbc
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0095fa40
void Owner_95fa40::SetValue(uint32_t value)
{
    mValue = value;
}
