// Setter (0x00c8ea30): store the dword argument in the member at +0x2d8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c8ea30 {
    char mPad[0x2d8];
    uint32_t mValue;                             // +0x2d8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00c8ea30
void Owner_c8ea30::SetValue(uint32_t value)
{
    mValue = value;
}
