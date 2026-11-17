// Setter (0x0095fa20): store the dword argument in the member at +0x7c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_95fa20 {
    char mPad[0x7c];
    uint32_t mValue;                             // +0x7c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x0095fa20
void Owner_95fa20::SetValue(uint32_t value)
{
    mValue = value;
}
