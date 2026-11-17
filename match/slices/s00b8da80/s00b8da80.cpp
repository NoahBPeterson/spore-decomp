// Setter (0x00b8da80): store the dword argument in the member at +0x184.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b8da80 {
    char mPad[0x184];
    uint32_t mValue;                             // +0x184
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00b8da80
void Owner_b8da80::SetValue(uint32_t value)
{
    mValue = value;
}
