// Setter (0x00941f80): store the dword argument in the member at +0x128.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_941f80 {
    char mPad[0x128];
    uint32_t mValue;                             // +0x128
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00941f80
void Owner_941f80::SetValue(uint32_t value)
{
    mValue = value;
}
